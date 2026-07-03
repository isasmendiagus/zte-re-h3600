# Stock WAN-ingress l3_en-arm — DEVICE-FREE decomp RE (2026-07-03)

## VERDICT (HIGH confidence)
**There is NO static HW table that stock programs and mainline misses to "arm l3_en"
for a WAN-ingress routed DN packet.** The task's leading hypothesis (Q1/Q2/Q4 — stock's
WAN/pppd/dhcp bring-up registers the WAN IP/MAC into a HW to-me/route table that mainline's
plain `ip addr add` never touches) is **REFUTED at the source** by four independent decomp
facts (below). The `l3_en=0` reading that motivated the hypothesis is almost certainly a
**noisy shared-latch artifact**: the authoritative trap reason for the mainline miss is
**0x54 = LOOK_UP_MISS**, which per DATASHEET:888 is *inside* the CLA hash lookup (the packet
WAS submitted to L3/forward), **not** a pre-CLA "l3_en never armed" disposition (that would
read as an SPA-parser reason such as 0x3f UDF_DMAC0). ⇒ The real gate is the previously-proven
**VERDICT B: a WAN/RGMII-ingress-specific CLA hash-LOOKUP MISS** (same key, same slot,
resident+valid entry, ~86% miss only on WAN-ingress) — an **engine-level** behavior that is
**not curable by writing any table**, so there is nothing in the stock decomp for mainline to
copy on this axis.

---

## Why the "stock writes a HW to-me/route table for the WAN IP" hypothesis is refuted

### (1) The WAN-IP HW ioctl is a STUB — no HW WAN-IP table exists
Stock registers ioctl handlers `sw_wancip_set`(0x410) / `sw_wancip_get`(0x411) /
`sw_wancip_del`(0x412) (switch.ko `fuc_table_node_create`, decomp_all_switch.c:975-977).
All three decompile to **`return 0;` — pure stubs** (decomp_all_switch.c:4897-4921). So even
the API that *looks* like "register the WAN client IP in HW" writes nothing. This directly
kills the "WAN IP → HW route/to-me table" mechanism: it does not exist in this build.
Corroborates the prior live read `local_ipv4 = 0` on both stock (while routing) and mainline.

### (2) `local_ipv4` / L3-default-flow context = 0 on both, set-fns have no in-module callers
- `cla_set_local_ipv4_addr` (tm.c:1088, claRegTable idx18 / 0x9238c09c) — never called from
  tm.ko/switch.ko init; live reads 0 on both (prior). The to-me DST-IP compare is inert.
- `cla_set_up_l3_default_flow_cfg` (tm.c:1608 → claRegTable 0x1e/0x1f/0x20) and
  `cla_set_dn_l3_default_flow_cfg` (tm.c:1701 → claRegTable **0x21/0x22/0x23/0x24**, incl.
  `da_known`=param_1[3]→reg0x22) have **NO callers anywhere in tm.ko or switch.ko** (pure API
  surface). Prior live reads: 0x1e-0x24 = 0 on BOTH, **including stock while it actively routes
  the live WAN** (agent a8117571). So the "DN L3 default-flow routing context / da_known" the
  task asked to check is **unarmed on stock too** — not the discriminator.
- `mac_req_ctrl` (cla_set_mac_req_ctrl_config tm.c:564, claRegTable idx5 = cla_config bit11) =
  **0 on both** (mac_lookup_en off). No MAC-lookup-requirement difference.

### (3) The to-me ONU-MAC table ALREADY contains the WAN (lan4) MAC on mainline
- lan4 is a **DSA slave** on the `sw` conduit; DSA slaves inherit the conduit's MAC, so
  **lan4's dst-MAC == the base switch MAC `f4:f6:47:0f:42:64`** (zx-eth-main.c:4529 seeds this
  as `sw_dev->dev_addr`; DSA slaves inherit it). The modem sends DN downloads to *that* MAC.
- The mainline driver `zx_eth_register_cpu_mac_slots` (zx-eth-main.c:6347) registers
  `sw_dev->dev_addr` (+0..3 in mac[5]) into the SPA ONU-MAC to-me table (0x14120, reg22/23) AND
  PM ram12 via `zx_register_cpu_mac`. base+0 == the lan4 dst-MAC ⇒ **the to-me MAC match
  succeeds on mainline**. This is stock's `tm_onu_mac_addr_set` (tm.c:41275 → spa_set_onu_mac_addr
  tm.c:26868 reg0x16/0x17 + pp_pm_set_onu_mac_ram_info tm.c:20318 ram_id0xc). Matches prior
  finding "ONU-MAC slots 0-3 identical stock↔mainline".
- NOTE: `pp_pm_set_onu_mac_ram_info` validates **index ≤ 0xf (16 slots)** (tm.c:20336). The
  mainline comment (zx-eth-main.c:6337) claiming stock replicates 4 MACs across "256 slots /
  64 groups" is a **misread of a live dump** — PM ram12 has only 16 entries; the driver's
  sl=0..243 loop over-runs into adjacent RAM but is harmless (the real to-me compare is the
  16-slot SPA/PM ONU-MAC, which already holds the base=lan4 MAC).

### (4) No HW route/FIB/LPM table exists at all
Prior exhaustive grep (ffe_forward_arm_hypothesis:260): L3 forwarding is **purely per-flow CLA
hash** — there is no route/LPM/FIB stage to program. `subnet_id` is a 4-bit ONU-MAC selector,
not a route; SADM is a policer. So "stock programs a DN route table for the WAN subnet" has no
HW target.

---

## The `trap_dmac` "5th slot" lead — CHECKED, ruled out
The SPA `trap_dmac` table (reg_id 24/25 @ NPP+0x141A0) traps to-me DST-MAC frames **pre-CLA**
(action_rsn 0x3f UDF_DMAC0). DATASHEET:519 flagged "RegTable declares 5 slots; the driver
clears 4." **Resolved: stock's own writer `spa_set_trap_dmac` (tm.c:26958) hard-validates
`param_1 < 4`** — stock software only ever manages **slots 0..3**. The reg-table `max_sub_idx=4`
is an off-by-one vs the API's `<4`; slot 4 is a phantom stock never touches. The driver's
`zx_eth_clear_spa_trap_dmac` clearing slots 0..3 (zx-eth-main.c:6367) is therefore **correct and
complete**. Also, a stuck trap_dmac slot would trap a constant dst-MAC at **~100%**, not the
observed ~14% — structurally cannot explain the partial rate. Lead closed.

---

## Reconciling l3_en=0 vs the real signal (the crux)
- `stock_wan_ingress_lookup_compare` read stock DN reason 0x49 (OTHERS→forward)/l3_en=1 while
  forwarding, and mainline (prior/DATASHEET) 0x54 LOOK_UP_MISS/l3_en=0 — **but both findings
  explicitly flag the `desIn*` latches as shared/non-per-packet/noisy** ("counters are
  authoritative"), and #476 read the reason as 0x2c/0x11 (decode stale).
- Decisive logic: **0x54 = LOOK_UP_MISS lives INSIDE the CLA hash lookup.** A packet only
  reaches the hash-lookup stage if it was submitted as L3-routable (l3_en effectively set). A
  genuinely-`l3_en=0` packet would take a pre-CLA disposition (SPA-parser reason, e.g. 0x3f, or
  an L2/SBRG bridge path), never 0x54. So the ~86% that "miss" **did** get L3-submitted and then
  **missed the hash** — matching `wan_ingress_perpacket_key` VERDICT B (engine-level miss with a
  resident+valid entry), NOT an upstream l3_en arm.
- The single l3_en=0 read = the shared latch caught a non-L3 frame (ARP/UP-ACK/control), not the
  trapped DN data packet. This is the same latch-aliasing that made naive gparsehashkey sampling
  catch the UP key 100% of the time.

⇒ **The task's premise ("~86% arrive with l3_en=0") does not survive scrutiny; the ~86% arrive
L3-submitted and LOOK_UP_MISS at the CLA hash.** There is no l3_en-arming table to port.

---

## What actually differs (the real, still-open gate) and the correct fix direction
The residual gate is **VERDICT B**: a WAN/RGMII-ingress (RX ring-1) CLA hash-lookup that hits
only ~10-14% for a byte-identical key at the correct, resident, valid slot — while the *same
entry* hits **100% from LAN/GePHY ingress** (hitrate_rootcause). pos32 (the WAN-ingress key bit)
was the one real key-domain difference and is **already fixed + slot-proven in both directions
(#474)**, yet the miss persists ⇒ the residual is **below the key/slot layer — in the WAN-ingress
lookup engine/regime itself.** This is not a value stock writes to a register; stock's identical
CLA config (cla_config 0x600, hash_poly 0x00e400e4, outspace 0x4 → single global way0) simply
*does* hit 99% from the same ingress. The differentiator is dynamic/pipeline, not static.

**Concrete fix path (NOT a table write — empirical, per the perpacket finding's leads b/c):**
1. **Clean same-5-tuple A/B, LAN-ingress vs WAN-ingress** with an identical resident entry
   (DSA tc-flower on lan2 vs the WAN download) — isolates the ingress pipeline as the sole
   variable and quantifies the WAN-only miss with everything else pinned.
2. **Reliable per-packet descriptor read** for a trapped WAN-ingress DN *data* packet (via the
   kill-client-retransmit gparsehashkey trick, not the noisy desIn latch): read the true
   action_rsn to confirm 0x54 (in-CLA miss) vs any pre-CLA reason. If pre-CLA → re-open l3_en; if
   0x54 → the fix is in the WAN-ingress hash-probe/pipeline (ring-1 DN NAPI classify race, or a
   WAN-ingress inner-hash/way regime), NOT in any to-me/route table.
3. Do **not** chase more static table replication on this axis — the static surface
   (CLA config, ONU-MAC to-me, local_ipv4, L3 default-flow ctx, mac_req_ctrl, trap_dmac,
   SPA/DPA parse-enable, classify RAMs, PM chain, per-flow ram0/ram1/ram2) is now **fully
   exhausted and proven identical/inert**; the WAN-IP ioctl is a stub.

---

## Confidence ranking
- **HIGH**: WAN-IP HW-table hypothesis refuted (ioctl stub + local_ipv4=0 + to-me MAC already
  present on mainline + no FIB stage). No l3_en-arming table exists to port.
- **HIGH**: trap_dmac 5th-slot ruled out (stock API is 4 slots; would be 100% not 14%).
- **HIGH**: 0x54 LOOK_UP_MISS is in-CLA ⇒ packets are L3-submitted; l3_en=0 was a noisy latch.
- **MEDIUM-HIGH**: the true gate is VERDICT B (WAN-ingress engine-level lookup miss), curable
  only by the empirical WAN-vs-LAN A/B + reliable descriptor read, not a stock-table copy.

## Method / provenance (device untouched, no code edits, no commits)
Pure static RE of `tasks/00.10.02.re-stock-kmods/findings/decomp_all_{tm,switch}.c` +
`linux-v6.6/drivers/net/ethernet/zte/{zx-eth-main.c,zx-fpga-reg-tables.h}` +
`DATASHEET.md`, cross-referenced against the prior on-device findings
(stock_wan_ingress_lookup_compare, wan_ingress_perpacket_key, hitrate_rootcause,
ffe_forward_arm_hypothesis). No device access, no sub-agents.
