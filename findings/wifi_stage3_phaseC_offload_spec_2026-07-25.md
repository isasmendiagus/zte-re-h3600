# WiFi Stage-3 Phase C — HW-offload spec: WAN⇄WiFi hardfast flows on the CLA/PM path (2026-07-25)

Device-free RE + design. Sources: mainline `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`
(all bare `:NNNN` cites below), the v6.6 netfilter/flowtable core in the same tree, stock decomp
(`tasks/00.10.02.re-stock-kmods/findings/decomp_all_{tm,switch,plat_zxylzb_9128S,idmfdb}.c` +
fresh vmlinux FFE decompilation), and the Phase-A live stock dumps
(`findings/wifi_stage3_stock_ssid_correlation_2026-07-07.md`,
`findings/stock_ssid_correlation_dumps_2026-07-23/`). Phase B (slow path) is CLOSED and
validated OTA (`findings/wifi_stage3_phaseB_e2e_realclient_2026-07-07.md` close-out).

**Phase C goal:** WAN⇄WiFi routed/NAT traffic rides the switch's HW forwarding path — a CLA
hardfast flow + PM NAT rewrite, egressing to fabric ports 6/7 with the ssid — so the CPU is out
of the per-packet *decision* path (it remains the thin IDM⇄mt76 shuttle; there is no WED-style
zero-CPU path on this SoC, per `findings/wifi_offload_feasibility_2026-07-04.md` §2).

---

## 0. Headline

1. **The crux is a non-problem on this tree: WAN⇄WiFi flows are ALREADY offered to our
   driver's flow-offload callback today** — the nft flowtable fan-out delivers *every* flow of
   the flowtable to *every* bound block callback regardless of which device the flow egresses
   (net/netfilter/nf_flow_table_offload.c:855-862), our cb is bound via the DSA-conduit
   delegation for the existing `{lan2, lan4}` flowtable, and this tree's local patch
   force-sets `NF_FLOW_HW_BIDIRECTIONAL` (net/netfilter/nft_flow_offload.c:364-373) so both
   directions arrive. The DN (egress-wlan1) rule is then **declined by our own H4 guard**
   (`zx_ft_egress_regport` returns INVALID for any non-DSA egress dev, :3568/:3687-3699).
   **The entire Phase-C trigger is therefore a driver-side egress-resolution change**, exactly
   the mediatek "late resolution" pattern — no netfilter, mac80211, or mt76 changes.
2. **The recipe is the eth recipe with ONE field widened**: the CLA entry's `gemport_uni_id`
   (which mainline already uses for egress steering, = egress regport) becomes the WLAN
   logical port `essid = 0x10 | (idm_ring<<3) | ssid` (Phase-A live-proven, e.g. 0x1c =
   idm1/ssid4). Mainline's packer truncates it to 4 bits (`& 0xf`, :2871); the field is 12
   bits wide (entry bytes 1-2), so the fix is one extra OR term. Everything else — key,
   hashes, ways, `direct`+`da_known`, PM `flow_info`/`next_hop`, external DDR table —
   is byte-identical to the working eth DN flow.
3. **The DN egress delivery leg already exists in the driver** (Phase B built it,
   HW-untested): a frame the fabric HW-forwards to ports 6/7 lands in the IDM RX ring,
   `zx_idm_poll` decodes the ssid and direct-`ndo_start_xmit`s it into the bound vif
   (:1794-1806). The IDM RX ring receives *only* hw-forward egress — never traps
   (`findings/wifi_stage3_qmg_queue5_consumer_re_2026-07-07.md` §3) — so `idm_rx_count`
   ticking is itself proof of HW forwarding.

---

## 1. THE CRUX — how a bridged/routed-WiFi flow gets offered to and installed in the CLA/PM path

### 1.1 What the kernel actually does (v6.6, this tree — all cites verified in-tree)

- **Flowtable register time** (`nft add flowtable ... flags offload; devices={...}`): per
  device, `nft_register_flowtable_net_hooks` calls the flowtable type's `setup(...,
  FLOW_BLOCK_BIND)` = `nf_flow_table_offload_setup` (net/netfilter/nf_tables_api.c:8174-8176;
  nf_flow_table_inet.c:67/77/87). Its logic (nf_flow_table_offload.c:1186-1207): if the dev
  has `ndo_setup_tc` it is called **directly** with `TC_SETUP_FT` and an error **aborts
  flowtable creation** (nf_tables_api.c:8177-8178); only if `ndo_setup_tc` is **NULL** does
  the *indirect* path (`flow_indr_dev_setup_offload`, net/core/flow_offload.c:605-631) offer
  the bind to drivers registered via `flow_indr_dev_register`.
- **Flow add time**: `flow_offload_add` → (HW_OFFLOAD flag) → workqueue →
  `flow_offload_work_add` → `nf_flow_offload_tuple`, which delivers a **TC_SETUP_CLSFLOWER**
  rule per tuple direction to **every** block cb on the flowtable's single cb_list
  (nf_flow_table_offload.c:855-862, list splice :1107-1108). **There is no per-device flow
  routing** — a cb bound from lan4 sees flows whose egress is wlan1. A cb declining (<0) is
  skipped; if no cb accepts, the flow just stays SW (:896-905).
- **Flow creation is 100 % SW** — the forward-hook `flow add @ft` rule
  (`nft_flow_offload_eval`, nft_flow_offload.c:291-390) has **no device-list check**; the
  device list only determines where the *ingress hooks* (SW fastpath) and block binds live.
- **This tree's local patch**: `nft_flow_offload_eval` force-sets `NF_FLOW_HW_BIDIRECTIONAL`
  (nft_flow_offload.c:364-373, H3600 comment) — upstream only tc act_ct sets it — which is
  why both directions' rules reach our cb today (the eth UP offload depends on this).

### 1.2 Consequence: the offer already happens; our own guard is the only gate

With the rig's existing flowtable `{ hook ingress; devices = { lan2, lan4 }; flags offload }`
(`scratchpad/rig.py:342`) and routed NAT WAN⇄wlan1 (mainline's Phase-B topology: wlan1 is
**routed** — 192.168.50.0/24 — NOT bridged; bridging conflicts with the bound rx_handler,
Phase-B e2e findings): a WAN⇄WiFi-client TCP flow hits the forward hook, the flow is created,
and both CLSFLOWER rules are delivered to `zx_ft_setup_cb` (:3816) via the conduit binding
(DSA delegates `TC_SETUP_FT` to the conduit master, net/dsa/slave.c:1688-1710 →
`zx_eth_setup_tc` :3904). The DN rule arrives with `FLOW_ACTION_REDIRECT` dev = **wlan1**
(routed: the flow's dst dev IS the vif) and the client MAC already resolved into the ETH
mangle / resolvable via `zx_ft_resolve_nh(wlan1, daddr)` (:3525 — a plain `neigh_lookup` on
wlan1, which works: the client is an ARP neighbor there). `zx_ft_egress_regport(wlan1)`
returns `ZX_FT_EGRESS_INVALID` → H4 decline (:3687-3699). **That decline is the single point
to extend.**

### 1.3 Rejected alternatives (and why — so nobody re-litigates)

- **(a) Put wlan1 in the flowtable device list**: mac80211 netdevs ALWAYS have
  `ndo_setup_tc` (both ops sets: net/mac80211/iface.c:833/:942) which returns `-EOPNOTSUPP`
  unless the wifi driver implements `net_setup_tc` (driver-ops.h:1522-1537; **mt76 has none
  in this tree**) → *flowtable creation itself fails*, and the indirect path never fires for
  a dev whose ndo exists. Dead without wireless-stack changes.
- **(b) dev_fill_forward_path resolution (the literal mediatek mechanism)**: mt7915's
  `net_fill_forward_path` exists only under `CONFIG_NET_MEDIATEK_SOC_WED`
  (mt76/mt7915/main.c:1611-1641) — **absent from `build/.config`** — so
  `ieee80211_netdev_fill_forward_path` returns -EOPNOTSUPP, which **aborts the whole path
  walk** (net/core/dev.c:717-718). mediatek (mtk_ppe_offload.c:185-237, :89-116) re-walks
  the path in-driver at REPLACE time, but only profits because WED provides the path
  terminator. Not usable here; also unnecessary (1.2).
- **(c) flow_indr_dev_register claiming br-lan**: viable *for a bridged topology* (bridge
  masters have no ndo_setup_tc) and would additionally give the UP direction a SW-fastpath
  ingress hook on br-lan — but mainline's topology is routed, our cb already gets the flows,
  and the indr cb double-delivery (direct via conduit + indr via bridge) needs dedupe.
  Deferred; revisit only if the topology moves to a bridge (see §5 Q6).

### 1.4 How STOCK triggers its WiFi hardfast install (decomp-traced, for equivalence)

Stock has **no WiFi-specific trigger**. The generic FFE ("fast forwarding engine",
vmlinux-builtin) learns per-packet from TX/inject hooks — WiFi UP frames feed it via
`idm_fdb_hook_xmit` → `ffe_learn_skb(skb, 3)` (decomp_all_idmfdb.c:167/:204, softirq-only,
skb-only input) — and, once a flow passes the state/threshold gates
(`ffe_npu_create_flow`@vmlinux c0458cc8: flow state "confirmed" + packet-count threshold +
`hf_entry_police2` admission filter, decomp_all_switch.c:11960), calls the registered NPU
driver: `npu_drv_create_flow` (switch.c:12242) → `hf_set_l3_entry` (switch.c:1823) →
`sw_acl_l3_hardfast_session_add_part_1` (switch.c:1476) → `zte_api_fast_l3_session_add`
(tm.c:59030) → `tm_acl_fast_add_v4v6`/`cla_set_hash_table` + PM writes. **The WiFi-ness
enters exactly once**: `get_sw_port_from_devname` (switch.c:4515) maps the resolved egress
(DN, switch.c:1697) or ingress (UP, `sw_acl_setMtchInfo` switch.c:1123-1135) netdev *name*
to `essid = 0x10 | (ring<<3) | ssid` via `IfName2WlanIdmMap` — that value becomes the CLA
entry's `gemport_uni_id` (DN) / the session inport (UP). Teardown = FFE aging polling HW
liveness (`hf_query_l3_status` → `zte_api_fast_l3_session_use`) + explicit delete.

**Mainline equivalence:** nft flowtable *is* our FFE (ct-established 5-tuple learn, offload
offer, stats/GC aging, DESTROY); the Phase-B `zx_wifi_dispatch[16]` (idm,ssid)→vif binding
table *is* our `IfName2WlanIdmMap`. The missing piece is only the vif→essid resolution at
REPLACE time — the same place stock does it.

### 1.5 RECOMMENDED TRIGGER (concrete)

- **Trigger 0 — first validation (no netfilter at all):** the existing `fttest` debugfs
  white-box (`install <cookie> <saddr> <daddr> <sport> <dport> <eg_regport>`, :6759+)
  **already accepts** `eg_regport 28`; it drives the real reserve+install path. The only
  code between it and a correct WiFi entry is the 4-bit truncation in `zx_ft_pack_cla`.
- **Trigger 1 — production:** extend `zx_ft_egress_regport` (or a wrapper at its :3687 call
  site): if `odev` matches a **bound** `zx_wifi_dispatch` node's `wlan_ndev`, return that
  node's `essid = 0x10 | (idm<<3) | ssid`; keep the H4 decline for everything else. Gate new
  acceptance behind a debugfs knob `ftwifi` (default **OFF**) so an unconfigured boot is
  byte-identical to today's baseline. The UP direction (egress = WAN) needs **no trigger
  change** — it is already accepted by the existing UP path; only its HW matching is open
  (§2.2).
- **Trigger 2 — bridged topology (deferred):** `netif_is_bridge_master(odev)` →
  `br_fdb_find_port(odev, nh_mac, 0)` → if the port is a bound vif, resolve as above.
  Open: locking context (FT workqueue holds zx_hwlock, not rtnl — verify
  `br_fdb_find_port`'s requirements before implementing). Optionally + design (c) for the
  br-lan SW-fastpath hook.

---

## 2. THE FLOW-INSTALL RECIPE (exact, field-by-field)

### 2.1 DN — WAN→WiFi (the priority direction: modem-backed download)

Identical to the **proven** eth DN flow (~95 MB/s validated) in every field except one.
Install path: `zx_ft_flow_reserve` (:3302, collision declines C2/H2 unchanged) →
`zx_ft_install_recipe` (:3079). For egress = essid (≥0x10 ≠ `ZX_WAN_REGPORT` 5), the
existing `is_dn = eg_regport != ZX_WAN_REGPORT` (:3741) and `up_idx_fix = (eg ==
ZX_WAN_REGPORT)` (:3151-3153) decisions are **already correct** with no change.

| piece | value for a WiFi DN flow | same as eth? | source |
|---|---|---|---|
| CLA key (12 w) | `zx_ft_build_key(proto, s, d, sp, dp, is_wan=true)` — ex_rule 0x90 5-tuple, kb[4] bit0 = WAN-ingress extraction | ✅ identical | :2892 |
| hash slots | poly-1 HW engine raw → 5 ways ram2..6; + poly-0 `ram2[raw0&0xff]` (DN) | ✅ identical | :2632/:2939/:2965 |
| `cla[0]` | `idx_lo<<24 \| 0x000044 \| gemport_uni_id packed into bits 23:12` | ⚠ **THE ONE CHANGE** — see below | :2871 |
| `cla[1..3]` | `0xfa11c0<<8 \| idx_hi`; `0x608`; `0` | ✅ identical | :2874-2887 |
| `cla[4]` | `proto<<24 \| 0x00100069` = valid_en + extr 0x90 + **direct** + **da_known** | ✅ identical (is_wan=true already sets both) | :2857-2866 |
| `cla[5..8]` | 5-tuple compare bytes | ✅ identical | :2867-2878 |
| cmd_flow_id | legacy DN packing byte3=0x03/byte4=flow_id → ≥0x400 → **external DDR flow_info** | ✅ identical | :2778-2795 |
| PM ram1 next_hop[pm_slot] | client MAC + NAT'd (client) IP | ✅ identical mechanics; MAC from `zx_ft_resolve_nh(wlan1, daddr)` — plain ARP neigh on the routed vif | :3100-3103, :3525 |
| PM ram0+external flow_info | `dmac_en, hl_ttl_en, chk bits, dport/sport/dip/sip enables, next_hop_idx=pm_slot, subnet_id=1` | ✅ identical | :2999, :3048 |
| PM ram6/ram3 | `sub[0]=pm_slot`; `cmd[0]=0x00800000` no-op | ✅ identical | :3133/:3138 |
| FDB | **not required** — `da_known` is an entry bit (key-compare + rewrite-gate), not an FDB lookup; fttest installs with a fabricated MAC and no FDB entry | ✅ identical | :2842-2868, fttest :6759 |

**The one change — `gemport_uni_id` packing.** Stock's stored-entry decoder proves the field
is 12 bits across entry bytes 1-2: `gemport_uni_id = byte2<<4 | byte1>>4`
(`cla_set_hash_table`, decomp_all_tm.c:3366-3550; Phase-A dump decoded value **28 = 0x1c**).
In `cla[0]` (little-endian word = entry bytes 0-3) that is bits [15:12] (low nibble) + bits
[23:16] (high byte). Mainline writes only `((eg_regport & 0xf) << 12)` (:2871) — correct for
regports 1-5, truncates 0x1c → 0xc. Fix:

```c
cla[0] = ((u32)idx_lo << 24) | 0x000044 |
         (((u32)eg_regport & 0xf) << 12) |          /* gemport_uni_id[3:0]  */
         ((((u32)eg_regport >> 4) & 0xff) << 16);   /* gemport_uni_id[11:4] */
```

No-op for every existing eth value (1-5 have zero high bits) — zero regression surface.

**Live stock cross-check** (the ground truth this reproduces —
`stock_ssid_correlation_dumps_2026-07-23/cla_flows_filtered.txt`): WiFi client flows
`cmd_flow_id 1136-1140`: `da_known=1, valid_en=1, direct=1, inport=0, outport=0,
gemport_uni_id=28, tcnt_gpid_rp_en=1, windata0=proto(6/17)`; PM `flow_info dir=1,
next_hop_idx=165/167 → next_mac=fa:f4:9f:69:7e:e5, next_dip=192.168.1.128; dmac_en=1,
smac_en=1, nat_dport=…, hl_ttl_en=1`. Contrast wired flows: `da_known=0, direct=0,
gemport_uni_id=5`. Notes: (i) stock leaves `outport=0` — so do we (mainline never wrote it);
(ii) whatever enables gemport application (`tcnt_gpid_rp_en`) is already effective in
mainline's template — eth egress steering via this field is HW-validated (:2817-2827,
on-device 2026-07-03); (iii) stock sets `smac_en=1`, mainline leaves it 0 — worked for all
eth cases; if the OTA client rejects frames with a stale SA, revisit (§5 Q3).

**DN datapath after the CLA hit** (end-to-end):
```
WAN ingress (lan4/MAC4) → CLA hardfast hit (direct+da_known, gemport=essid)
  → PM NAT rewrite (dmac→client MAC, dip→client IP, dport, TTL)
  → fabric egress port 6/7 (+ssid in the pipeline descriptor)
  → IDM RX ring DMA, desc word1 bits[18:16]=ssid, [19]=valid, [31]=ring
  → zx_idm_poll (:1715): ssid decode (:1750-1751) → zx_wifi_dispatch[ssid+ring*8]
  → direct ndo_start_xmit into the bound vif (:1794-1806) → mac80211 → air
```
Everything below "fabric egress" is Phase-B code, **built but never exercised** (the ring
has never received a frame on mainline: `idm_rx_count = 0` always, because nothing ever
steered fabric traffic to ports 6/7 — `findings/wifi_stage3_phase1_2026-07-07.md`). The
stock RE guarantees the ring is fed by exactly this verdict (qmg_queue5 findings §3: IDM RX
= hw-forward egress only, no trap ever). **Risk R1**: unknown whether some QMG/greg config
must additionally be live for fabric→IDM delivery on mainline (stock init is replayed, so
expected-working, but this leg is the novel one — validation V1 settles it first).

### 2.2 UP — WiFi→WAN

The UP entry is the **existing, HW-validated eth UP recipe unchanged**: egress WAN →
`up_idx_fix` (cmd_flow_id = pm_slot → internal ram0[pm_slot]), `gemport_uni_id = 5`,
`direct+da_known`, key with `is_wan=false` (:3151-3153, :2806). The trigger needs no change
(egress lan4 is a DSA port; `ft_up_en` defaults ON). What's genuinely open is **HW
matching**: the packets now ingress the fabric from the IDM ring (inport 6/7, via the
Phase-B `zx_wifi_rx_handler` → `zx_idm_xmit` injection), not from a GePHY wire.

- Stock's installer keys the UP session with `inport = essid` (switch.c:1123-1135), yet
  every live-captured stored entry printed `inport = 0` (Phase-A dump — including the UP
  ones, `v4_up:3`), and mainline's eth entries also leave the entry inport 0 and match
  wire-LAN ingress fine. So the stored-entry "inport" is evidently not a required match
  field for rule 0x90.
- **Risk R2 (open)**: whether a ring-ingress (port 6/7) frame extracts the same key/bucket
  as a LAN-wire-ingress frame (kb[4] bit0 clear). Phase B proved ring-ingress FORWARD-class
  frames DO traverse the CLA (they fell through to the PP bridge because *no rule matched* —
  the inport-1..5 catch-alls don't cover 6/7, phaseB e2e §bisect step 5). If the UP flow
  misses, capture `desIn`/hash on-device — do NOT guess an extraction bit.

**Priority: DN first.** DN is the dominant traffic (download data), rides the novel egress
leg, and its ACK return path (UP) staying SW is exactly the state eth offload shipped in for
a while (UP=SW is a working configuration; `ft_up_en` can force it). Validate DN → then UP.

### 2.3 Both directions via nft (production behavior)

Each direction is its own cookie/REPLACE (bidirectional force-set, §1.1). With `ftwifi` on:
the DN cookie resolves egress wlan1 → essid → installs; the UP cookie resolves egress lan4 →
regport 5 → existing UP path installs. NAT mangles arrive per-direction exactly as for eth
(dnat on DN, snat on UP — parser :3629-3672). `zx_ft_resolve_nh` on wlan1 resolves the
client's neigh entry (Phase-B left a PERMANENT ARP for the test client as belt-and-braces).
Flow aging: unchanged eth semantics — stats keepalive (:3803), DESTROY → `zx_ft_flow_untrack`.

---

## 3. ORDERED DRIVER-CHANGE PLAN (all in zx-eth-main.c; reuse, don't fork)

1. **`zx_ft_pack_cla` (:2806)** — widen the gemport_uni_id packing (one OR term, §2.1).
   Also widen the `eg_regport` *log* formats if any assume one digit. Audit remaining
   `eg_regport` consumers for 4-bit assumptions: `is_dn` compare (:3741, fine — essid ≥ 0x10
   ≠ 5), `up_idx_fix` (:3151, fine), fttest passthrough `eg_regport & 0xff` (:6835, fine).
2. **WiFi egress resolver** — new small helper `zx_ft_wifi_essid(e, odev)`: scan
   `e->zx_wifi_dispatch[0..15]`; if a node is `enabled` and `wlan_ndev == odev`, return
   `0x10 | (idm<<3) | ssid`; else INVALID. Call it in `zx_ft_flower_replace` where the H4
   guard currently declines (:3687-3699): if `READ_ONCE(e->ft_wifi_en)` and the helper
   resolves, proceed with `eg_regport = essid`; otherwise decline exactly as today. Keep
   `zx_ft_egress_regport()` itself untouched (it is the DSA-only resolver `fttest resolve`
   regression-tests).
3. **`ftwifi` debugfs knob** (mirror `ftup`, :565/:7059-ish) — `e->ft_wifi_en`, default
   **0**. Un-configured boot = today's baseline bit-for-bit; `fttest`-driven installs are
   explicit operator actions and don't need the gate.
4. **`fttest`** — no functional change required (`install ... 28` already reaches
   pack_cla). Extend `resolve <devname>` output to also report a wifi-bind resolution when
   `ft_wifi_en` is on (cheap white-box for the new helper).
5. **Deferred (explicitly NOT this pass):** bridged-master resolution (Trigger 2);
   ram2 catch-all trap rules for inports 6/7 (stock-parity slow-path, useful later so
   unmatched ring traffic stops relying on the PP bridge path); `smac_en` rewrite; per-ssid
   TM shaping; multicast (MTRANS) parity.

Build: the usual `make zImage` (driver is builtin); no new Kconfig. All new behavior is
gated (knob default-off) → safe to boot.

## 4. ON-DEVICE VALIDATION PLAN

Discrimination rule (the heart of it): **HW-forwarded ⇔ `idm_rx_count`/`idm_rx_per_ssid[]`
and `idm_wifi_rx_dispatched` climb ~1:1 with delivered packets while `tm_rx_fabric` /
`tm_wifi_rx_dispatched` (slow-path trap dispatch) and `qmg_dn_trap` stay FLAT** — the IDM RX
ring only ever carries hw-forward egress (qmg_queue5 findings §3), and the slow path only
ever uses TM q4 ring0. Counters: `pipeline_stats` (:7313 — QMG dn/up sw_fwd/hw_fwd/hw_trap,
CLA fwd 0x1cc3c0) + `stats`/`wifi_bind` (driver counters).

- **V0 — boot + baseline.** RAM-boot the new build (manual U-Boot, `pci=nomsi
  pcie_aspm=off` first). Eth regression quick-pass (`regress.py` guards; sustained download
  LAN-local). Confirm `ftwifi` reads 0; counters baseline; `idm_rx_count = 0`.
- **V1 — white-box DN egress leg (the novel leg, no client needed).** hostapd up; bind
  wlan1 ↔ (1,4) (`wifi_bind wlan1 1 4`); `ftwifi 1`. `fttest install <cookie> <WAN-side
  tuple> 28` with a synthetic 5-tuple whose packets we can generate ingressing the WAN port
  (e.g. from the modem side / hping from the WAN network toward the NAT'd tuple). Watch:
  CLA fwd counter climbs, `idm_rx_count`/`per_ssid[4]` climb (**first-ever nonzero = R1
  retired**), `idm_wifi_rx_dispatched` climbs, `tm_rx_fabric`+`qmg_dn_trap` flat. Frames
  visible OTA (client not required to accept them — fttest's fabricated next-hop MAC is
  fine for this leg; radio/`station dump` tx counters as witness). If `idm_rx_count` stays
  0: R1 — capture desOut latch + QMG wifi-queue counters, investigate (throttled reads,
  file-then-cat; NO devmem batches over the console).
- **V2 — real DN e2e (the deliverable): modem-backed WAN→WiFi download.** Client associates
  FIRST, then bind; routed NAT (Phase-B topology) + nft flowtable (rig `offload` recipe) +
  `ftwifi 1`. Client pulls a large file through the WAN uplink. PROOF = all of: (a)
  throughput ≥ multiple-×-slow-path (slow-path baseline measured first, same file); (b)
  `idm_rx_count` ≈ packet count of the transfer while `tm_wifi_rx_dispatched` and
  `qmg_dn_trap` stay flat; (c) `top` CPU: softirq/sys far below the slow-path baseline; (d)
  conntrack/flowtable shows the flow `[OFFLOAD]`. Record MB/s + counter deltas.
- **V3 — UP.** With DN proven: client-side upload (or just the download's ACK stream —
  stock's own WiFi capture had `v4_up:3`). Watch `cla_up_fwd`-equivalent (CLA fwd), the
  UP QMG counters, `tx_injected` vs trap counters. If UP misses (R2): desIn/hash capture,
  new finding, decide is_wan-keying experiment on evidence — not by guessing.
- **V4 — regression + safety.** `ftwifi 0` → re-run an eth download (unchanged numbers);
  reboot without any knobs → baseline behavior; `fttest destroy` path on a live WiFi flow
  (uninstall zeroes all ways + poly0 + PM, :3225 — unchanged); dmesg clean (no WARN/BUG).

Console discipline (binding, learned 2026-07-25): one short command per REPL call; no
devmem loops over UART; bulk reads → on-device file → single cat. DTR power-cycle only as
last resort (also resets the modem — verify WAN uplink is back before V2).

## 5. OPEN QUESTIONS (explicit — do not guess past these)

1. **R1**: does fabric→IDM-RX delivery need any extra QMG/greg enable on mainline? (Stock
   init is replayed; the leg is simply unexercised. V1 settles.)
2. **R2**: UP ring-ingress key extraction — same bucket as LAN-wire ingress? (V3 settles;
   stock's `inport=essid` session field vs stored-entry `inport=0` discrepancy noted §2.2.)
3. **SMAC rewrite**: stock sets `smac_en=1` on WiFi DN flows, mainline never enables it
   (source of the replacement SMAC = PM ram 0xc CPU-MAC block, unconfirmed). Matters only
   if the OTA client validates SA; revisit on evidence.
4. **Raw `ndo_start_xmit` into mac80211** (:1801) bypasses qdisc/HARD_TX_LOCK (stock did
   the same into its proprietary driver). If mac80211 misbehaves under load, fall back to
   `dev_queue_xmit` (loses a few cycles, gains locking correctness).
5. **cla[1] constants** 0x11/0xfa and `cla[2]=0x608` semantics (inherited unknown; the
   template is HW-proven on eth, and gemport steering demonstrably works with it).
6. **Bridged topology** (Trigger 2): `br_fdb_find_port` locking from the FT workqueue;
   indr-block double-delivery dedupe. Only relevant if wlan1 moves into a bridge.
7. **External DDR flow_info fetch index low 7 bits** (inherited from eth DN; whole
   128-entry block filled as workaround, :3034-3040).
8. **MTU/frag**: IDM_RX_SKB_SIZE 0x6C4 bounds the HW-forwarded frame size; standard-MTU
   TCP is fine; jumbo/frag behavior unprobed.

## 6. Source index (spot-check)

- Mainline driver: pack `:2806-2890`; key `:2892`; hashes `:2632/:2939`; ways `:2965`;
  reserve `:3302`; install `:3079`; flow_info `:2999`; ext DDR `:3048`; uninstall `:3225`;
  replace/H4 `:3581/:3687-3699`; egress resolver `:3568`; UP gate `:3719-3728`; setup_tc
  `:3904/:3866/:3816`; idm poll+dispatch `:1715/:1794-1806`; idm xmit+tag `:1859/:327-338`;
  vif bind `:2005/:7198`; tm-trap dispatch `:4970`; fttest `:6759`; pipeline_stats `:7313`.
- Kernel: nf_flow_table_offload.c `:855-862/:1107-1108/:1186-1207`; nf_tables_api.c
  `:8174-8180`; nft_flow_offload.c `:30-37/:48-77/:94-168/:187-219/:221-272/:291-390/
  :364-373 (local patch)`; flow_offload.c `:432-460/:605-631`; dev.c `:697-735`;
  br_device.c `:393-437`; mac80211 iface.c `:825-834/:875-931/:941-1021`; mt7915 main.c
  `:1611-1641`; mtk_ppe_offload.c `:89-116/:185-237/:239-478`; dsa slave.c `:1688-1710`.
- Stock decomp: get_sw_port_from_devname switch.c:4515; hardfast add chain
  switch.c:1476/1697/1734/1823/11850/12242 → tm.c:59030/54261/52521/49213/3366; setMtchInfo
  switch.c:1035/1123-1135; FFE vmlinux c04511f4 (learn) / c044e484 / c0458cc8 (create gate)
  / c0458714 (npu_enable); idmfdb.c:167/204 (learn feed), :60 (DN dispatch); teardown
  switch.c:1866/1929/11776.
- Findings: Phase-A correlation + dumps (2026-07-07/23); ssid encoding spec (2026-07-07);
  qmg_queue5 consumer RE (2026-07-24); Phase-B e2e close-out (2026-07-25);
  nat_offload_re (2026-07-03); wifi_offload_feasibility (2026-07-04).
