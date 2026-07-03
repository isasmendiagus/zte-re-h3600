# FFE-install port spec — mainline HW-offload (2026-06-24)

From workflow `ffe-install-port-spec` (decode live capture + diff vs driver + flow-offload trigger).
Turns the live stock FFE-install capture (stock_ffe_live_install_capture_2026-06-24.md) into a
mainline make-or-break test + a driver-implementation plan.

## MAKE-OR-BREAK manual test (run on mainline, device-bound)
Goal: does the FULL 3-part install (CLA ram2 + PM ram0 flow_info WITH rewrite-arm + PM ram1 next-hop)
flip cla_tx_fwd/acl_required, where the earlier ram2-ALONE slot-sweep left them at 0? The untested
additions are PM flow_info `fi[0]=0x0de80005` (rewrite-enable bits, NOT bare 3) + PM next-hop + the
cmd_flow_id→ram0 link.

Test 5-tuple: TCP 172.31.9.50→192.168.9.50:5201, sport 40000 (matches the driver's hardcoded cla[]).
debugfs sequence (on mainline; substitute the REAL dst-host MAC):
```
# baseline peek (single-arg poke = read; result in dmesg)
echo "0x9238c3b8" > poke ; echo "0x9238c3c0" > poke   # acl_required hi16 ; cla_tx_fwd
# (2) FFE extract arm (one-time)
echo "1 98 22038608 000058a1 0 0 f00ff000 ffffffff ffffffff 0fffffff 0 0 0 0 0 0 00700000 00092492 0" > clawrite
echo "0 9 93929190 97969594 9b9a9998 9f9e9d9c 00150151" > clawrite
# (3) PM ram1[5] next-hop (dst IP 0xC0A80932 + dst MAC)
echo "1 5 c0a80932 cbb68169 00006c70 0 0 0 0 0" > pmwrite ; echo "1 5" > pmpeek
# (4) PM ram0 flow_info fwd@5 + rev@0x405 WITH rewrite-arm (0x0de8|idx) + brute-fill
echo "0 5 0de80005 0014035c 0 0 0 0 0 0" > pmwrite
echo "0 405 0de80005 0014035c 0 0 0 0 0 0" > pmwrite
echo "0de80005 0014035c 0 0 0 0 0 0" > pmfill
# (5) CLA forward entry — brute-fill all 520 (sidesteps unverified hash-key inport bits)
echo "03005044 fa110005 00000608 80000000 06000049 32ac1f00 32c0a809 519c4009 00000014 0 0 0 0 0" > fill520
# (6) matured flow from 172.31.9.50:  iperf3 -c 192.168.9.50 -p 5201 --cport 40000 -t 120
#     (for a manual mainline test, a one-way TCP-SYN stream matching the 5-tuple via the LAN ingress
#      also exercises the CLA hit; bidirectional iperf not strictly required to move cla_tx_fwd)
# (7) re-peek the two counters
```
- byte0x04 = 05 (`fa110005`) sets cmd_flow_id→flow_info N=5 (vs the driver's stale `fa11c000`).
- proto at byte 0x13 = 0x06 (TCP). fi[0]=0x0de80005 carries the rewrite-enable bits (the earlier
  sweep used bare 3 = no rewrite = no forward).
- PASS: cla_tx_fwd (0x9238c3c0) and/or acl_required hi16 (0x9238c3b8) CLIMB → full install engages HW
  forwarding → driver fix is the whole job. FAIL (flat): an UPSTREAM ingress gate blocks the transit
  packet before the CLA forward stage (SPA/classify/admit) → that RE comes first. Localize via whether
  acl_required moves at all. Confounder: if cla_tx_TRP climbs instead, the flow is being CPU-trapped.

## Driver implementation plan
### Workstream A — fix the install payload (zx-dsa.c zx_install_l3_recipe / zx_dsa_cls_flower_add)
- A1: real CLA field-packer — pass saddr/sport/dport/ip_proto in (currently only daddr); build cla[]
  from the literal template overwriting per-flow bytes: proto@0x13 (NOT 0x09), src_ip@0x15 / dst_ip@0x19
  (per-16-bit-short LE of host-order u32, SPEC.md), sport@0x1d / dport@0x1f raw LE. word3=0x80000000;
  byte0x10=0x49 (inport/outport map UNSOLVED — keep live default).
- A2: link cmd_flow_id (bytes 0x03/0x04) to the ram0 flow_info addr N used in zx_pm_wr(p,0,N,fi).
- A3: fix PM flow_info word0 — `fi[0]=(0x0de8u<<16)|next_hop_idx` (rewrite-enable bits) instead of
  bare 3 (zx-dsa.c:638). Keep fi[1]=0x0014035c.
- A4: make next_hop_idx (fi[0] low byte) == the ram1 addr used in zx_pm_wr(p,1,I,nh).
- A5: real next-hop MAC from FLOW_ACTION_MANGLE eth-dst rewrite (or neigh on daddr), replacing the
  hardcoded 6c:70:cb:b6:81:69.
- A6: keep fill520 brute-fill until validated; then switch to single slot = zx_cla_hash_raw(key)&0xff.

### Workstream B — wire the auto-trigger (★ DECISIVE finding)
DSA does NOT route nf_flow_table HW offload through `ds->ops->cls_flower_add`. On TC_SETUP_FT,
`dsa_slave_setup_tc` delegates to the CONDUIT master netdev's `ndo_setup_tc` (net/dsa/slave.c) — and
the conduit `zx_eth_netdev_ops` has NO ndo_setup_tc, so the flowtable path dead-ends at -EOPNOTSUPP.
THIS is why real flow-offload never reached the cls_flower hook (manual tc skip_sw did).
- B1: add `.ndo_setup_tc = zx_eth_setup_tc` to zx_eth_netdev_ops (MediaTek PPE pattern,
  mtk_ppe_offload.c): TC_SETUP_BLOCK/TC_SETUP_FT → flow_block_cb bind → cb handles
  TC_SETUP_CLSFLOWER FLOW_CLS_REPLACE/DESTROY → install/remove.
- B2: factor the parse+pack+write (A1-A5) into a helper callable from both the conduit cb and the
  existing zx-dsa hook. The CLA/PM helpers already live in the conduit module.
- B3: conduit netdev likely needs NETIF_F_HW_TC in features for the block to bind (MTK gates on
  tc_can_offload) — verify/set.
- B4 (no code): nftables flowtable `flags offload`. All kernel configs already enabled.

### ★ Trigger CONFIRMED empirically (2026-06-24): the 2nd packet of a 5-tuple
The FFE installs on the **2nd packet of a given {proto,sip,dip,sport,dport}** (1st pkt trapped+installs,
every subsequent pkt HW-forwarded; Δfwd=n−1). Applies to **TCP AND UDP**; **ICMP never** installs
(no L4 5-tuple). NOT bulk/established/bidirectional-gated — one-way single-tuple installs immediately.
⇒ Workstream B should hook the conntrack flow-confirmed event (IPS_CONFIRMED / post-first-packet
softpath) for TCP+UDP, exclude ICMP — mirroring stock ffe_learn_skb→hf_set_l3_entry. For the manual
mainline test, just send ≥2 packets of the test 5-tuple (the entry is pre-installed, so they should
HW-forward from packet #1).

### Sequencing
Workstream A first, validated by the manual test above. Only if the manual full-install flips the
counter is B worth wiring. If the manual test FAILS, the upstream ingress gate is the blocker (RE that
first) — neither A nor B.

## ★ MAKE-OR-BREAK RESULT (2026-06-24): FAIL — full install necessary-but-NOT-sufficient
Ran the full 3-part install on mainline (boot OK; install readback verified: PM ram1[5] next-hop,
ram0[5]=0de80005 rewrite-arm, fill520 520/520) + a 400-pkt matching flow. Counters:
acl_required (0x9238c3b8 hi16) = 0 → 0 (FLAT); cla_tx_fwd (0x9238c3c0) = 0 → 0 (FLAT);
**cla_tx_trp (0x9238c3c4) +400 (= the entire flow, all CPU-TRAPPED).** So every matching packet reached
the CLA but was trapped; acl_required never lifted off zero. ⇒ the PM rewrite-arm pieces were NOT the
missing part. The gate is UPSTREAM of the CLA forward/ACL-submit stage: mainline classifies this transit
5-tuple as TRAP regardless of a fully-armed ram2+PM+next-hop. Consistent with the carried HW-forwarding
dead-end. The stock FFE install must write SOMETHING BEYOND ram2+PM that arms the forward path (makes
acl_required climb / l3_en=1 for the flow). NEXT = enumerate the COMPLETE stock FFE install (every MMIO
write in zte_api_fast_l3_session_add → tm_add_acl_flow_rule + the switch.ko ffe_learn/hf_set_l3_entry
path) to find that forward-arm; the decisive empirical fallback is a stock before/after full-state diff
across an FFE install (the 2nd-packet transition).

## Open items (carried)
- MAKE-OR-BREAK unknown: does the full install flip the counters (vs ram2-alone=0)? Untested PM pieces.
- cmd_flow_id→ram0 N linkage not byte-pinned (pmfill sidesteps).
- hash-key header/inport bits for a mainline regport not derived (fill520 sidesteps).
- byte0x10 inport/outport packing for arbitrary regports unsolved (0x49 = live default).
- fi[0] 0x0de8 exact bit assignment + fi[1] low bits not pinned (copy wholesale for L3 transit).
- PM ram1 next-hop 8-word layout from prior groundtruth, not re-captured (verify via pmpeek).
- conduit NETIF_F_HW_TC presence unverified.
- real next-hop MAC + egress regport from FLOW_ACTION_MANGLE/REDIRECT not yet decoded.
