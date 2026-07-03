# Multi-flow selectivity + nf_flow_table/conntrack auto-offload investigation (2026-07-02)

Device: mainline **#458** (live, no reboot). All tests via `tc flower` on the DSA user
port lan1 + host UDP flow-gen (src 172.31.9.50:50010 → 192.168.9.50:<dport>, routed via
the device lan1→lan4). Counters: cla_tx_fwd 0x9238c3c0, cla_tx_trp 0x9238c3c4,
MAC4/lan4 wire-TX 0x92300718. Reads via debugfs `poke` peek (loglevel 8).

---

## PART 1 — MULTI-FLOW SELECTIVITY (the win, hardened)

### Rig re-verify + single-flow selectivity (only flow A installed)
| flow | cla_tx_fwd | cla_tx_trp | mac4_tx | verdict |
|---|---|---|---|---|
| A = UDP …:50010→…:53 (installed) | **+400** | flat (+1 bg) | **+400** | HW FORWARD (wire egress) |
| dport 5555 (NOT installed) | flat | **+401** | flat | TRAP (selective) |

Rig solid, reproduced the milestone.

### Two-flow coexistence test (A dport 53 + B dport 1053 both installed via tc)
Installed flow B second: `tc filter add … dst_port 1053 … redirect lan4` → driver built
the recipe and **fill520-wrote flow B's key to all 520 CLA buckets** (dmesg
`recipe: …:1053 … -> 520/520 CLA buckets`).

| flow (both A+B in tc) | cla_tx_fwd | cla_tx_trp | mac4_tx | verdict |
|---|---|---|---|---|
| A = dport 53 (installed FIRST) | **+0 FLAT** | **+401** | flat | **TRAPS** — B overwrote A's buckets |
| B = dport 1053 (installed LAST) | **+400** | flat | **+400** | **FORWARDS** — owns all buckets |
| dport 5555 (not installed) | flat | +403 | flat | TRAPS |

**⇒ fill520 is a single-entry hack. Two installed flows CANNOT coexist.** The most
recently installed flow's fill520 clobbers every one of the 520 buckets, so only ONE
5-tuple HW-forwards at a time; the earlier flow immediately starts LOOK_UP_MISSing
(its stored key was overwritten with the new flow's key → bucket key-compare fails).

### `tc filter del` behaviour (cls_flower_del)
Deleted flow B (`tc filter del dev lan1 ingress pref 49151`): dmesg logged
`[phase6] cls_flower_del port1 cookie=…`, tc removed the filter (only A left in
`tc filter show`), **but the driver's `zx_dsa_cls_flower_del` returns -EOPNOTSUPP and
clears NOTHING in HW**.

| flow (B deleted from tc; only A in tc) | cla_tx_fwd | cla_tx_trp | mac4_tx | verdict |
|---|---|---|---|---|
| B = dport 1053 (tc-DELETED) | **+400** | flat | **+400** | **STILL FORWARDS** (stale/leaked HW entry) |
| A = dport 53 (still in tc) | flat | **+400** | flat | still TRAPS (buckets still hold B) |

**⇒ del is a HW no-op: a deleted flow keeps HW-forwarding.** The CLA buckets are never
invalidated on FLOW_CLS_DESTROY.

### Productization limitations documented (both are real bugs)
1. **fill520 = single-entry** (`zx_install_l3_recipe`, zx-dsa.c:756; also `zx_ft_install_recipe`,
   zx-eth-main.c:2324). It writes the packed entry to ram2[0x100]+ram3[0x80]+ram4[0x40]+
   ram5[0x40]+ram6[8] = 520 buckets to sidestep slot prediction. Real multi-flow needs
   **per-slot placement**: compute each flow's hash slot (the HW hash engine / `hashcalc`
   debugfs, already validated) and write the entry only to its computed bucket, so
   distinct 5-tuples occupy distinct buckets and coexist.
2. **cls_flower_del / FLOW_CLS_DESTROY does not remove the HW entry** (returns -EOPNOTSUPP,
   log-only). Must invalidate the flow's bucket(s) on delete, else entries leak and (with
   fill520) collide. Blocker for any churny auto-offload.

---

## PART 2 — nf_flow_table / conntrack AUTO-offload plumbing

### Result: TC_SETUP_FT does NOT bind, no callback fires. Two stacked gaps, first is fatal.

**GAP 1 (fatal): the DSA conduit netdev `sw` has no `.ndo_setup_tc`.**
- `lan1` → `lower_sw` → conduit is the `sw` netdev (confirmed on-device via
  `/sys/class/net/lan1/lower_sw`).
- `sw` is created with **`zx_sw_netdev_ops`** (zx-eth-main.c:4290), which has NO
  `.ndo_setup_tc` entry. Only **`zx_eth_netdev_ops`** (the unused `idm%d` netdevs) has
  `.ndo_setup_tc = zx_eth_setup_tc`.
- Kernel FT delegation: `dsa_slave_setup_tc(lanN, TC_SETUP_FT)` →
  `dsa_slave_setup_ft_block()` (net/dsa/slave.c:1688) does
  `if (!master->netdev_ops->ndo_setup_tc) return -EOPNOTSUPP;` — master = `sw`, whose
  ops lack it → **EOPNOTSUPP before the driver is ever reached.**
- Directly attaching tc to `sw` also can't offload: `sw` also lacks `NETIF_F_HW_TC`
  (set only on the `idm%d` netdevs, zx-eth-main.c:5374). **Empirically verified on-device:**
  `tc qdisc add dev sw clsact` → RC 0; `tc filter add … flower skip_sw …` →
  **"Operation not supported"**; same filter without skip_sw → installs **`not_in_hw`**;
  and **`zx_ft_setup_cb` / `[phase6/ft]` NEVER fired** (no dmesg) → the flow-block was
  never bound. (This is why the milestone saw "conduit doesn't bind" — it is not a
  binder_type issue; the conduit netdev has no setup_tc hook at all.)

**GAP 2 (would surface after Gap 1 fixed): `zx_eth_setup_block` rejects the FT binder.**
- `zx_eth_setup_tc` routes both `TC_SETUP_BLOCK` and `TC_SETUP_FT` into
  `zx_eth_setup_block` (zx-eth-main.c:2535).
- `zx_eth_setup_block` (2505) returns -EOPNOTSUPP unless
  `binder_type ∈ {CLSACT_INGRESS, CLSACT_EGRESS}`. A flowtable bind carries
  `FLOW_BLOCK_BINDER_TYPE_FT` → rejected. So even with a conduit setup_tc, TC_SETUP_FT
  would still not bind.

### What already works (would fire once the gaps are wired)
`zx_ft_setup_cb` (2484) handles `TC_SETUP_CLSFLOWER` — the exact command the
nf_flow_table offload core dispatches to a bound FT block (FLOW_CLS_REPLACE/DESTROY).
`zx_ft_flower_replace` (2409) already parses the 5-tuple + FLOW_ACTION_REDIRECT +
FLOW_ACTION_MANGLE(eth-dst) and installs via `zx_ft_install_recipe`. Because the
conntrack/flowtable path carries the next-hop dmac as a MANGLE action taken from the
flow, the manual-tc CONFIG_NET_ACT_PEDIT / neigh limitation does **not** apply to the
auto path — the recipe code is present and correct; it is simply **unreachable**.

### Wedge / environment dependencies for a LIVE auto-offload demo
- **No `nft` on the device** (busybox; only `tc`+`iptables` present). An offload
  flowtable (`table … flowtable f { … flags offload; devices = {lan1,lan4} }`) can only
  be created with `nft` → the TC_SETUP_FT bind can't be driven from userspace on-device
  right now even after the plumbing fix. Need an `nft` binary (or an in-kernel/tc test
  harness) to exercise it.
- **A real conntrack-ESTABLISHED flow is required to trigger `flow_offload_add`.** The
  rig's 192.168.9.50 is fictional/one-way → conntrack never reaches ESTABLISHED → the
  flowtable never promotes/offloads. A live responder on lan4's subnet is needed. This
  LAN→LAN direction avoids the WAN-RX one-wrap-wedge ([[zte-redwedge-unicast-cpu]]), and
  CPU→LAN egress is already SOLVED ([[zte-tx-egress-blocker]]), so the return path is
  viable with a real host; but with a fictional dst there is nothing to establish.

### Recommendation — concrete wiring for full auto-offload (in priority order)
1. **Add `.ndo_setup_tc = zx_eth_setup_tc` to `zx_sw_netdev_ops`** (zx-eth-main.c ~4290 struct).
   This is the single essential missing wire; without it the FT delegation and any
   tc-on-conduit offload are dead. (Safe, small.)
2. **Set `NETIF_F_HW_TC` on the `sw` netdev** (features + hw_features) so
   `tc_can_offload(sw)` is true (needed for a direct-on-`sw` flow block; MTK pattern).
3. **Accept `FLOW_BLOCK_BINDER_TYPE_FT` in `zx_eth_setup_block`** (alongside the two
   CLSACT binders) so TC_SETUP_FT binds `zx_ft_setup_cb`.
4. Then the flowtable core dispatches TC_SETUP_CLSFLOWER → `zx_ft_flower_replace` →
   `zx_ft_install_recipe` (already parses REDIRECT + MANGLE-dmac from the flow).
5. **Prerequisites from Part 1 (must land before enabling auto, or it self-corrupts):**
   replace fill520 with per-slot hash placement (multi-flow coexistence), and implement
   real bucket invalidation on FLOW_CLS_DESTROY (auto flows churn constantly → the
   single-entry clobber + stale-entry leak would be immediate and fatal).
6. To demo: add an `nft` binary to the initramfs (or write a tiny kernel/tc FT test),
   and use a rig with a live host at the routed dst so conntrack reaches ESTABLISHED.

---

## Device state left behind (healthy, #458, NO reboot)
- Flow A (UDP …:50010→192.168.9.50:53 → redirect lan4) re-installed and **HW-forwarding**
  (verified +300 fwd / +300 mac4_tx, trap flat). Only one flower filter on lan1
  (pref 49152, dport 53, in_hw=1) — matches the milestone's healthy end-state.
- The stale flow-B bucket contents were overwritten by re-installing A (B now traps).
- `sw` clsact qdisc (Part-2 test) removed. No SW bridge exists (brctl empty).
- Rig intact: host enxc8a362e95900 = 192.168.1.50/24 + 172.31.9.50/24; route
  192.168.9.0/24 via 172.31.9.1; permanent ARP 172.31.9.1→f4:f6:47:0f:42:64.
- UART bridge running (:9998/:9999). No code committed; no driver edits made on-device.
</content>
</invoke>
