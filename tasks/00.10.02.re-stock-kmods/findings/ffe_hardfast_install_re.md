# Phase 6 / Stage 0a — Stock FFE "HFF" hardfast-install path (static RE)

2026-06-04, branch phase6-hw-offload. Read-only RE of decomp_all_switch.c + decomp_all_tm.c.
ZTE's HW flow-offload is called **HFF = Hardware Fast Forward** (engine namespace "NPU"). This maps
the full conntrack→HW-session install chain. Concrete CLA/QMG register writes live in one function
(`zte_api_fast_l3_session_add` @ tm.c:59030, ~900 lines) — extracting those = Stage 0a-deep + the
koprobe dynamic trace (UNKNOWNS at bottom).

## Architecture — the callback registration (switch.ko)
`l3_hardfastReg` (decomp_all_switch.c:1386) registers the L3 offload handlers with the NPU/HFF core:
```
npu_hff_register(&handlers, &sizes)   // switch.c:1407 ; npu_hff_register def @ switch.c:10920
  handlers = { hf_set_l3_entry, hf_del_l3_entry, hf_query_l3_status, hf_entry_police2 }
  sizes    = { 0x14, 0x14, 0x14, 0x14 }   // each callback's entry size = 20 bytes
```
Called from the switch init path (switch.c:2734). So the NPU/HFF core (kernel's conntrack/flow side)
invokes these 4 callbacks; switch.ko implements them; the actual chip writes are one layer deeper in
tm.ko. "NPU" here is ZTE's name for the HW-fast-forward subsystem (switch-fabric CLA-hash hardfast),
NOT a separate processor — `ffe_get_npu_enable` is a global enable gate (confirm in 0a-deep).

## (i) Offload decision / trigger
- The slow path runs `ffe_receive_skb(skb,3)` (switch.c:629,656,702) and `ffe_learn_skb(skb,3)`
  (switch.c:877) on RX — these feed the NPU/HFF learning. Once a flow qualifies (conntrack
  ESTABLISHED + the NPU core's policy), the core calls **`hf_set_l3_entry`**.
- Direction + WAN/LAN classification: `FROM_WAN`/`TO_WAN` (switch.c:1423/1440) classify by netdev
  name (`pon`/`ptm` = GPON/PTM WAN, `eth%u` = the 5 MACs, filtered by
  `zte_api_sw_mac_set_port_macfiltermode[port]`). The session carries a `direction` field (0=up/
  toward WAN, 1=dw/toward LAN) — tm.c:59121,59138.

## (ii) Install chain (conntrack flow → chip)
```
NPU/HFF core
  → hf_set_l3_entry(ptSession)                         switch.c:1825
    → sw_acl_l3_hardfast_session_add(ptSession)        switch.c:1800
      → sw_acl_l3_hardfast_session_add_part_1(...)     switch.c:1478  (builds the entry)
        → zte_api_fast_l3_session_add(entry, &result)  switch.c:14651 (thin) → tm.c:59030 (REAL)
```
`session_add_part_1` reads the session struct (param_1) fields and packs a local entry, then calls
`zte_api_fast_l3_session_add(local_b8, &local_cc)` (switch.c ~1734). Session-struct offsets seen:
+0x34 (u16), +0x4c (byte), +0x4d (byte), +0x51 (byte), +0x58..0x68 (5 dwords = the flow KEY used by
status, see below).

## (ii) Entry format (the ptFastL3Session passed to tm.c:59030)
From `zte_api_fast_l3_session_add(byte *ptFastL3Session, uint *result)` (tm.c:59032+):
- +0x00  direction (0=up,1=dw)                                  tm.c:59121,59138
- +0x68  byte flag; +0x6a u16 (a port/index)                    tm.c:59141-59143
- +0x98  u16, +0x9a u16, +0x9c byte, +0x9d byte, +0x9f byte     tm.c:59134-59136,59122-59123
  (+0x9d == 0xff is a SENTINEL meaning "field absent" → sets local_df/e0=0; else present —
   looks like an optional NAT/translation field, tm.c:59124-59132)
- It builds HW-entry locals: `local_e4[0xbc]` (188-byte entry?), `local_148[100]`, `local_15c[0x14]`
  (__memzero'd at tm.c:59118-59120) — the assembled hardfast table entry, written under
  `fast_api_busy_lock` (tm.c:59140). Full key/action field map = Stage 0a-deep (read 59140..59966).

## (iii) Install mechanism (the chip writes) — LOCATED, not yet extracted
`zte_api_fast_l3_session_add` @ **decomp_all_tm.c:59030** (ends ~59966) is where the HW table entry
is programmed (takes `fast_api_busy_lock`, assembles the entry, writes it via the TM indirect-table
interface — almost certainly the CLA hash RAM per memory zte-cla-ram-layout [ram2-6 per-inport hash
w/ action] + QMG egress mapping). **Exact regs/RAM-id/hash scheme = UNKNOWN until 0a-deep + koprobe.**
Sibling HW APIs (tm.ko): `zte_api_fast_l3_session_del` @ tm.c:59966, `_use` @ 57358, `_clr` @ 57322,
`_stat` @ 57396.

## (iv) Teardown / aging
- Delete: `hf_del_l3_entry` (switch.c:1868) → `sw_acl_l3_hardfast_session_del` (switch.c:1850) →
  `_del_part_3` (switch.c:1750) → `zte_api_fast_l3_session_del` (tm.c:59966).
- Status/aging: `hf_query_l3_status` (switch.c:1931) → `sw_acl_l3_hardfast_flowstatus` (switch.c:1892)
  reads the 5-dword key (ptSession+0x58..0x68) and calls `zte_api_fast_l3_session_use(0,&key,&status)`
  (tm.c:57358). The NPU core polls this to know if the HW session is still active (refreshes/ages the
  conntrack entry accordingly). So aging is HW-status-driven, not a pure SW timer.

## (v) RX-from-HW (the offloaded fast path)
Inferred (consistent with memory zte-hw-forwarding-deadend): the FIRST packet of a flow misses the
CLA hash → trapped to CPU → conntrack establishes → `hf_set_l3_entry` installs the hash entry; then
subsequent packets HIT the CLA hash → action = forward-to-egress-port (+ NAT/MAC rewrite from the
entry) → QMG → MAC egress, bypassing the CPU. TODAY mainline never installs hash entries → CLA traps
everything → all-software forwarding. (Confirm the hash-hit action path in 0a-deep.)

## (vi) QoS hook
`hf_entry_police2` (switch.c:1149) is the 4th registered callback — per-session policing/shaper. This
is where HW QoS attaches to an offloaded flow (Stage 5). Read its body when we get there.

## UNKNOWNS → next sub-iterations
- **0a-deep (static):** read `zte_api_fast_l3_session_add` body (tm.c:59140-59966) → the exact entry
  key/action field layout + which CLA/QMG registers/indirect-RAM it writes (absolute phys via
  npp_base 0x921c0000) + the hash scheme. Same for `_del`. Update DATASHEET with the regs.
- **0b (koprobe dynamic):** boot stock, kotrace {hf_set_l3_entry, zte_api_fast_l3_session_add,
  zte_api_fast_l3_session_use, ffe_receive_skb, ffe_learn_skb}, run an iperf flow LAN→WAN through the
  stock router, dump /proc/kotrace_dump → live call order + r0-r3 (the real session struct ptr +
  entry values); pair with `fpga -r` reads of the CLA/QMG regs before/after install to capture the
  actual written values. Grounds 0a-deep in real data.
- **0c:** Linux flow_offload/flowtable hooks (ndo_setup_tc TC_SETUP_FT, nf_flow_table_offload,
  flow_offload_action) + mtk_ppe reference → the minimal driver hook set.
- **0d:** design doc (HFF ⇄ Linux flowtable mapping).
