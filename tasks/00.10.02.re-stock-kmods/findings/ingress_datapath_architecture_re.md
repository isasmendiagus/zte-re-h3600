# Ingress datapath architecture (RX: LAN → CPU) — synthesis

Status: synthesized 2026-06-01 from the SPA / PP_PM / port-numbering RE agents + prior live findings.
Companion to the egress model (`eth_pipeline_architecture_2026-05-28.md`). Ties the per-block decodes
into one coherent ingress model + the port-numbering per stage + where port1 dies.

## The pipeline (LAN frame → CPU)
```
SMAC[port] RX  ──►  [MAC→SPA admit/handoff]  ──►  SPA  ──►  SDET  ──►  CLA  ──►  QMG  ──►  SIPC  ──►  TM RX ring → napi → conduit → DSA demux → lanN
   (phys MAC)         (the OPEN gate)            (uni)     (uni)    (regport)   (trap)   (shared)
```

## What each stage does (RE'd) + confidence
- **SMAC[port] RX** — per-port MAC receives off RGMII. RX-ok counter @ `mac_off(port)+0x780`. ✅ (port1 RX-ok climbs clean = frames arrive).
- **MAC→SPA admit/handoff** — DECODED 2026-06-01 (`mac_to_spa_admit_re.md`): this is the **SOPC↔SMAC bridge `0x921d9068`** (NPP[0x19068]). bit(port+5)=`phy_mac_ready` (RO, HW sets on serializer bond), bit(port)=`mac_rx_to_fabric_en` (SW admits RX into the crossbar, set ONLY if ready). **port1 dies HERE** (SPA `rcv_uni1` low, SDET `uni1`≈2). H1: port1's `phy_mac_ready` (bit6) never asserts → admit bit1 never set → bridge closed (RX-ok climbs wire-side, before the bridge). The READY bit is RO + needs the serializer bond — can't be poked (explains the earlier failed enable-bit poke). Stock bonds port1's serializer (pings jack2); mainline's smac_init doesn't → the fix is per-port serializer bring-up, not the admit bit. Numbering = raw/logical (port1=bit1/bit6).
- **SPA** (0x921d4000) — parse + classify. match-RAM (ram0, 11 ent) + hash-RAM (ram5, 8 ent) = **PORTLESS** offset/mask/data byte-matchers → action; **mainline leaves them EMPTY (HW reset) → default admit/forward**. Per-entry `pkt_en`(0x14000/04/08)/`pps_en`(0x1400c/10) = all-on. The ONLY per-port SPA surface = `enty_pktdeal_cfg` `0x921d4300+port*0x14` (2-bit action per port×proto) — **port1 == port2 == port3 byte-identical** (live). ⇒ SPA classification EXONERATED for port1. (`spa_match_hash_ram_re.md`)
- **SDET** (0x921c4000) — per-uni frame-validate/VLAN-admit. maxframe per-port interleaved (port1=`0x4250[13:0]`=0x07cc, correct). Per-uni transport/drop counters `0x921c4160+uni*4`. Drop=0 (SDET doesn't drop port1; frames just don't reach it). (`port1_sdet_ingress_gate_re.md`)
- **CLA** (0x9238c014 indirect) — per-**inport** classify. ram2-6 hash table keyed by inport (=regport) → trap action `cpu_qid`. **regport2 (=port1) entries valid + identical to working regport3** (clapeek live). EXONERATED. (`cla_ram_layout_re.md`)
- **QMG** (0x9234c000) — enqueue/trap to CPU. hw_trap counter `0x9234c060`. Climbs for working ports, 0 for port1 (because nothing reaches it). Shaders/credit (SCH/DSCH/RED) ✅.
- **SIPC** (0x921cc000) — CPU↔fabric bridge. SHARED block (not per-port). drop counters `0x921cc004`=0. EXONERATED.
- **PP_PM** (0x9239c000) — per-**FLOW** edit/NAT (flow_id, NOT per-port); all entries no-op; symmetric. EXONERATED. (`pp_pm_table_re.md`)

## Port-numbering per stage (the definitive map — `port_numbering_map_re.md`)
| stage / block | index space | port1 = |
|---|---|---|
| SMAC counters / mac_off, desc egress-hint | **phys MAC index** = raw logical | 1 |
| SPA rcv_uni, SDET uni, RX-desc ingress `(desc[6]>>3&0x1f)-1` | **uni = logical** | 1 |
| isolation (0x83c0+p*4), FDB D2, CLA inport | **regport** `{1,2,3,4,5,0,6,7}` | **2** |
| greg/STP/port_closed | identity (variant A, CPU rejected) | 1 |
| PM in/out rules (0x20180/0x201a0) | raw logical | 1 |
TWO decomp "getPort" remaps: variant A (greg, identity LAN0..3) and variant B (`getPort@0x4f108` = regport table). DSA `zx_phys_port=identity` is CORRECT for greg. **No block mis-maps port1** — numbering is internally consistent.

## Where port1 dies + what's exonerated
port1: MAC1 RX-ok climbs (88 clean) → SPA rcv_uni1 low / SDET uni1≈2 → **lost at MAC1→SPA admit**, upstream of SDET, silent. EXONERATED (all identical/consistent to working ports): SPA classify (match/hash/pktdeal/pkt_en/pps_en), SDET, CLA, QMG, SIPC, PP_PM, port-numbering, MAC ctrl/en, isolation, STP, PM rules, broadcast flood.

## Open leads (next, bench)
1. **IDENTIFIED → confirm + fix.** The MAC→SPA admit = SOPC↔SMAC bridge `0x921d9068`. BENCH: read it with ports 1/2/3 up → expect port1 bit6(ready)+bit1(admit) clear, p2/p3 set. Then the fix is the per-port **serializer bring-up** (smac_init / FUN_40e50c40) so port1's `phy_mac_ready` asserts (stock does it). kotrace stock's port1 smac_init to capture the bonding sequence mainline misses.
2. ~~PM G.988~~ EXONERATED (`pm_g988_rules_re.md`): in/out rules are positive-match CAM, g988 rule-RAM 0x921e0248 empty in both stock+mainline. Not the gate. (But fix the latent g988-mode bit[3:2] bug + out-port idx1-7.)
3. ⚠️ **Numbering gotcha for pokes:** poke regport-blocks (isolation/CLA) with **regport2**, but SPA/SDET/uni blocks with **uni/logical 1**. Prior "no-effect" pokes may have hit the wrong port-space (regport2 on a uni block = uni2 = logical port2!). Re-audit before concluding a poke "did nothing".
4. Method: kotrace stock receiving on port1 to capture the MAC→SPA admit sequence (static diff exhausted).

## Bonus: latent DSA-TX egress-hint space (I-3, currently harmless)
TX egress hint `((eg+0x28)&0x3f)<<4` uses **phys-MAC-index** space; the DSA tagger puts the slave port in `skb->data[1]`. For LAN ports 0..3 logical == phys-MAC-index so it's fine TODAY, but if those spaces ever diverge the tag must be in the MAC-index space. Note for robustness.
