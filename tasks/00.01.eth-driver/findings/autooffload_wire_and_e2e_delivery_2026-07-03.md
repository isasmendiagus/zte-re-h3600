# Auto-offload plumbing WIRED + binds; e2e delivery blocked on 2nd NIC (2026-07-03)

**VERDICT:**
- **PART A — DONE.** The nf_flow_table/conntrack auto-offload flow-block now **BINDS** on
  the DSA conduit `sw` (no more EOPNOTSUPP). `zx_ft_setup_cb` + `zx_ft_flower_replace` are
  now REACHABLE from the FT/flower path — proven live on **#464**. The tc-flower multi-flow
  path on lan1 **still works** (A+B coexist, control traps) — NO regression.
- **PART B — NOT TESTABLE on current rig.** Only ONE host NIC has carrier (enxc8a362e95900
  on device lan1). No 2nd host NIC is cabled to a 2nd device LAN jack, so a real LAN→LAN
  responder (the definitive "HW forward delivers real traffic" proof) cannot be built without
  the user physically cabling a 2nd NIC. Exact setup documented below.

Device: mainline **#464** (`Linux (none) 6.6.0 #464 Fri Jul 3 00:57:16 UTC 2026`), fresh DTR
boot, RAM-only, NO reboot after boot. Build via `build_slotA.py` (module + zImage re-embed +
uImage wrap → tftp/zImage_dtb.uimg); DTR-boot via `tftp_boot_mainline.py`.

---

## PART A — the 3 edits (all in drivers/net/ethernet/zte/zx-eth-main.c)

### Edit 1 (two parts): conduit `sw` gets `.ndo_setup_tc`, adapted for its priv layout
1a. Added `.ndo_setup_tc = zx_eth_setup_tc` to the `zx_sw_netdev_ops` struct (was only on the
    `idm%d` `zx_eth_netdev_ops`). This is the single essential missing wire:
    `dsa_slave_setup_ft_block()` (net/dsa/slave.c:1696) delegates `TC_SETUP_FT` to
    `master->netdev_ops->ndo_setup_tc` where master = the conduit `sw`; without the hook it
    returned EOPNOTSUPP before the driver was ever reached.
1b. **Adapted `zx_eth_setup_tc` for the two DIFFERENT netdev_priv layouts** (this was the
    "check + adapt" the task called out — it was a real latent crash):
    - `idm%d` netdevs: `netdev_priv` holds `struct zx_eth_port *` (zx-eth-main.c:5500)
    - `sw` conduit:    `netdev_priv` holds `struct zx_eth *` directly (zx-eth-main.c:4407)
    The original `zx_eth_setup_tc` blindly did `port = *(zx_eth_port **)netdev_priv(ndev);
    e = port->eth;` — on `sw` that dereferences a `struct zx_eth *` as a `zx_eth_port *`
    → garbage/oops. Fixed: branch on `ndev->netdev_ops == &zx_eth_netdev_ops` and decode priv
    accordingly (sw → `e = *(zx_eth **)netdev_priv(ndev)`).

### Edit 2: `NETIF_F_HW_TC` on the `sw` netdev
In `zx_sw_netdev_create` (after the `netdev_ops` assignment): `ndev->hw_features |=
NETIF_F_HW_TC; ndev->features |= NETIF_F_HW_TC;` — gates `tc_can_offload(sw)` so a flow_block
binds on the conduit (MTK pattern; mirrors the idm%d netdevs).

### Edit 3: NOT NEEDED on this kernel (reverted; documented in-code)
The task said "accept FLOW_BLOCK_BINDER_TYPE_FT in zx_eth_setup_block". **On Linux 6.6 there is
NO `FLOW_BLOCK_BINDER_TYPE_FT`** (the enum in include/net/flow_offload.h stops at
CLSACT_EGRESS / RED_*). The nf_flow_table offload core binds its block with
`bo->binder_type = FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS`
(net/netfilter/nf_flow_table_offload.c:1135 `nf_flow_table_block_offload_init`) and dispatches
it via `ndo_setup_tc(dev, TC_SETUP_FT, bo)`. So the FT block **already matches the existing
CLSACT_INGRESS arm** of `zx_eth_setup_block` — no new case needed. Adding
`FLOW_BLOCK_BINDER_TYPE_FT` was a compile error (undeclared identifier). Reverted; left an
in-code comment for a future forward-port to a kernel that does have the FT binder type.

Module compiles clean (only pre-existing unused-function warnings). Full build succeeded;
`slotA.bin` NAND-pack step failed (body 0xe3fdb7 > NAND write size 0xc00000) but that is
IRRELEVANT — we TFTP-boot RAM-only from `zImage_dtb.uimg`, we do not flash NAND.

---

## PART A — verification (live on #464)

### (a) The FT/flower block BINDS now — EOPNOTSUPP-at-bind is gone, cb is reachable
`tc qdisc add dev sw clsact` then a flower `skip_sw` filter on `sw`:
```
tc filter add dev sw ingress protocol ip flower skip_sw ip_proto udp \
    dst_ip 192.168.9.50 dst_port 53 action mirred egress redirect dev lan4
```
dmesg (loglevel 8):
```
[phase6/ft] cookie=c52cd800 0.0.0.0:0->192.168.9.50:53 no resolved nh-MAC, skip
[phase6/ft] flower destroy cookie=c52cd800
```
→ **`zx_ft_setup_cb` FIRED and `zx_ft_flower_replace` ran all the way to next-hop-MAC
resolution.** Before this fix (see multiflow_and_autooffload_2026-07-02, "GAP 1 fatal") the cb
NEVER fired — the block was rejected at bind time with EOPNOTSUPP. **The plumbing is wired and
the block binds.** The REPLACE itself returns EOPNOTSUPP here ONLY because 192.168.9.50 is
fictional (neigh unresolved) and manual tc supplies no MANGLE-dmac — the exact
conntrack-vs-manual gap already documented; the real FT/conntrack path carries the next-hop MAC
as a MANGLE action, which `zx_ft_flower_replace` already parses (zx-eth-main.c:2562-2576).

### (b) REGRESSION — tc-flower multi-flow on lan1 STILL works (NO breakage)
Both filters install `in_hw in_hw_count 1`. UDP 172.31.9.50:50010 → 192.168.9.50:<dport>, 400/burst:
| flow | cla_tx_fwd | cla_tx_trp | MAC4/lan4 wire-TX | verdict |
|---|---|---|---|---|
| A dport 53 (installed) | **+400** | +1 | **+400** | HW FORWARD (wire egress) |
| B dport 1053 (installed) | **+400** | +5 | **+400** | HW FORWARD (coexists) |
| dport 5555 (NOT installed) | +0 | **+405** | +0 | TRAP (selective) |

Reproduces multiflow_perslot_impl_2026-07-03 exactly. `tc filter del` still invalidates
(dmesg: `flow del ... cleared raw=0xf6d5 (5 ways) rc=0` / `raw=0x1368`).

### The exact remaining gap for a LIVE auto-install fire
The plumbing binds, but a full conntrack→flow_offload_add→auto-HW-entry live fire still needs
BOTH of:
1. **An `nft` binary** (the device is busybox: only `tc`+`iptables`, no `nft`; `which`/`timeout`
   also absent). An offload flowtable (`table … flowtable f { flags offload; devices={lan1,lan4} }`)
   can only be created with `nft`. Add a static `nft` to the initramfs (or a tiny in-kernel/tc
   FT test harness).
2. **A real bidirectional conntrack-ESTABLISHED flow** — needs a live responder at the routed
   dst so conntrack promotes the flow to the flowtable and calls `flow_offload_add`. The rig's
   192.168.9.50 is fictional/one-way → never ESTABLISHED. (Same responder needed for PART B.)

---

## PART B — rig discovery + e2e delivery status

### Rig discovery (host `ip -br link` + ethtool)
| host NIC | carrier | notes |
|---|---|---|
| **enxc8a362e95900** | **YES, 1Gb/s** | the ONLY cabled NIC; on device **lan1**; has 192.168.1.50/24 (tftp) + 172.31.9.50/24 |
| enx2c9975313ea9 | NO (Link detected: no) | present but NOT cabled to anything |
| enx6c70cbb68169 | absent | not present on the host at all |

**⇒ Only one host NIC is cabled (to lan1). No LAN→LAN path exists.** The definitive
"HW offload delivers real usable traffic to a receiver" proof (rewritten DMAC = responder MAC,
TTL−1, seen on the responder's tcpdump) is **NOT testable** on the current physical rig.

The wire-egress counter proof stands (MAC4/lan4 TX **+400** per forwarded burst = packets
physically leave lan4), but the next-hop DMAC is still the SEEDED fallback
`6c:70:cb:b6:81:69` (dst 192.168.9.50 fictional → neigh unresolved), and there is no receiver
on lan4 (lan4 = the real WAN modem, must not be disturbed) — so real delivery is unproven.

### Hardware the USER must set up (morning physical task) for PART B + the auto-install fire
1. **Cable a 2nd host NIC to a 2nd device LAN jack** — e.g. plug `enx2c9975313ea9` into device
   **lan2** or **lan3** (NOT lan4 — that is the live WAN/PPPoE modem, do not disturb).
2. On the device, give that jack its own subnet, e.g. `ip addr add 192.168.20.1/24 dev lan2`,
   and make it the routed dst (avoid the 192.168.9.0/24-on-lan4 subnet so the WAN stays clear).
3. On the host 2nd NIC: `ip addr add 192.168.20.50/24 dev enx2c9975313ea9` and run a responder
   (`nc -u -l 53` or `iperf3 -s`); ensure the device can resolve its neigh (ping once so the
   ARP populates, or seed a permanent neigh).
4. Install the tc-flower offload for 172.31.9.50→192.168.20.50 redirecting to lan2 — the driver
   will resolve the REAL next-hop MAC (zx_resolve_nh_mac, zx-dsa.c:906) instead of the seed.
5. Send the flow from the host lan1 NIC; **tcpdump on the responder NIC** and confirm it
   RECEIVES the packets with dst MAC = responder MAC and **TTL decremented by 1**.
6. For the auto-install live fire: also drop a static `nft` binary into the initramfs, create an
   `nft` offload flowtable over {lan1, lan2}, and drive a real bidirectional (ESTABLISHED) flow
   through it — then `zx_ft_setup_cb`/`zx_ft_flower_replace` will auto-install the HW entry with
   the conntrack-supplied MANGLE next-hop MAC (no manual tc).

---

## State left behind (device healthy, #464, NO reboot)
- Device on **#464**, alive; UART bridge running (:9998/:9999); console loglevel 8.
- lan1 clsact + both flower filters REMOVED (each del exercised the invalidate path, rc=0);
  lan1 back to `noqueue`. sw clsact (Part-A bind test) removed. Datapath healthy.
- WAN/lan4 (real modem) untouched throughout — background WAN traffic (ingress=4) flows normally.
- Host rig restored (the fresh boot had dropped the 172.31.9.50 alias + route): enxc8a362e95900 =
  192.168.1.50/24 + **172.31.9.50/24**; route 192.168.9.0/24 via 172.31.9.1; permanent ARP
  172.31.9.1 → f4:f6:47:0f:42:64. **Keep the 192.168.1.50 alias** (tftp).
- Driver source edited in linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c (3 edits above);
  **NOT committed**.
