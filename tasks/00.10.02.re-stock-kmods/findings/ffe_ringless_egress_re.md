# FFE / ring-less CPU→LAN egress RE (2026-05-28)

DECOMP/STATIC RE + corpus reconciliation. Goal: explain HOW stock egresses a
CPU frame to MAC2 with ZERO DMA-ring activity (UP 0x10054/58/5c, DN
0x10064/68/6c, IDM 0x8040/44 all flat) while QMG sw_fwd (0x9234c044), SOPC
send2smac2 (0x921d9164) and MAC2 TX-OK (0x92280718) climb in lock-step.

Sources read myself this session: `decomp_all_plat_zxylzb_9128S.c`
(pon_tm_net_tx 6719, pon_tm_data_raw_send 6596, soft_insert_tx_1desc 6232,
pon_tm_dma_init 6277, pon_npp_sipc_init 2260, pon_npp_smct_init 3333,
pon_npp_spa_init 3345, the of_iomap bases 8949-9025), `decomp_all_switch.c`
(pdt_ethdrv_recv 531, pdt_ethdrv_send 789, swport_dev_xmit_fin 447,
pdt_ethdriver_init 300, sw_acl_l3_hardfast_session_add.part.1 1476),
`decomp_all_tm.c` (cla_set_local_ipv4_addr 1088, cla_set_oth_l3_pkt_action_cfg
1272, sipc_set_rx_en/cpu_up_en 20552/20610, pon_npp_smct_init,
**tm_switch_statistics @ 46560** — the downstream pipeline counter dump),
`zx-fpga-reg-tables.h` (qmg/sipc/smct/sopc base_offs), `regs/stock_eth_2mib.txt`.

---

## Headline (most likely mechanism)

**The CPU→fabric inject is the SMCT/SIPC CPU-port channel, NOT a TM/IDM DMA
ring — and the registers everyone has been calling "the TM UP/DN ring"
(0x921d0054/64) are actually the SMCT block, which is one of several CPU-fabric
transfer channels. The ring-less inject we can't see is almost certainly a
SIPC/SMCT path whose doorbell/FIFO we have never read live (0x921cc000 SIPC,
0x921d00xx SMCT control), distinct from the desc-ring kick at +0x54/+0x64.**

I could NOT positively confirm the exact inject write from the decomp — the two
visible software-TX functions (`pon_tm_net_tx` → `pon_tm_data_raw_send`) BOTH
unconditionally do BMU-alloc + memcpy + ring-kick, and both are contradicted by
the live measurement. So either (a) the live ICMP reply does not traverse
`pon_tm_net_tx` at all, or (b) there is a SIPC/SMCT fast-inject the decomp's
TX function doesn't cover. Evidence below; honest confidence stated per claim.

---

## What I ruled OUT (with decomp line refs)

### FFE / hardfast is for ROUTED flows, NOT the local ICMP reply — RULED OUT
- `sw_acl_l3_hardfast_session_add.part.1` (switch:1476) programs an **L3 NAT/
  routing session**: it carries ip4Addr, **natip, natport**, gemport, tcont,
  sessionid, pppoe (switch:1528-1640) and ends in `zte_api_fast_l3_session_add`
  (switch:1734) → `sbrg_add_ipv4table` (the HW L3 forwarding/NAT table). This is
  the WAN↔LAN routed/NAT fast path. The ping to 192.168.1.1 is **locally
  terminated** (br0's own IP), so no L3 session forwards it. Confidence HIGH.
- `ffe_learn_skb` / `ffe_receive_skb` in BOTH switch.c (13325/14063) and plat
  (9767) decompile as `halt_baddata()` stubs (the decompiler hit a region it
  could not decode — likely a PLT/import thunk table at 0x2c1xx-0x2c2xx; ALL ~80
  symbols in that address band are halt_baddata). So FFE **bodies are not in
  this decomp**. From the call sites: `ffe_receive_skb(skb,3)` gates the RX path
  (`pdt_ethdrv_recv` switch:629/656/702 — returns 0 ⇒ frame consumed by engine,
  nonzero ⇒ goes up to `netif_receive_skb`). It is an L2/L3 RX fast-forward, but
  for a frame destined to the *local* IP it must return nonzero (so the CPU IP
  stack can reply). FFE does not produce the locally-generated TX reply.
  Confidence MEDIUM-HIGH (inferred from call-site control flow; bodies missing).

### Both visible SW-TX paths force a ring kick — the universal contradiction
- `soft_insert_tx_1desc` (plat:6232-6244) is the ONLY kick: `dir==0 → *(tm_base+
  0x10054)=1`; `dir==1 → *(tm_base+0x10064)=1`. No third register. Confidence HIGH.
- `pon_tm_dma_init` (plat:6277) programs ONLY two ring desc-bases:
  UP `tm_base+0x10050`, DN `tm_base+0x10060`. There is no third TM ring. HIGH.
- `pon_tm_data_raw_send` (plat:6596) ALWAYS: `pon_tm_bmu_alloc_bp()` (6614) +
  `memcpy(BP_buffer, skb->data)` (6625) + desc + `soft_insert_tx_1desc` (6680).
  If this executed live, BMU 0x800c (BP index result) would CHANGE per frame and
  the kick/consume would tick. Live: BMU 0x800c byte-identical (0x04000800)
  across 600 frames, kicks flat. ⇒ **this function is NOT executing for the live
  reply.** Confidence HIGH (this is the crux).
- `swport_dev_xmit_fin` (switch:447) and `pdt_ethdrv_send` (switch:789) — the
  ethN per-port xmits — both re-point skb->dev to the lower mii_dev (priv 0x4c4
  = "sw"/"pon") and `dev_queue_xmit_sk` → bounce to `pon_tm_net_tx`. So the
  br0→eth3 path funnels here too. HIGH.

---

## The architecture I newly mapped (the productive lead)

Stock ioremaps FOUR separate windows (plat:8949-9025): `pon_base`,
`npp_base`, `tm_base`, `pp_base`, `idm_base`. From the reg-table base_offs +
the code's own offset arithmetic, **npp_base = tm_base = phys 0x921c0000**
(they alias the same 2 MiB window via different DT nodes). Sub-blocks:

| block | code base | phys | reg-table base_off | role |
|---|---|---|---|---|
| IDM | npp+0x8000 | 0x921c8000 | (idm) | CPU-port DMA ring (idm0/1) — flat live |
| **BMU** | tm+0x8000 | 0x921c8000 | (d2xxx) | bp-pool alloc 0x800c/10/14 — flat live |
| **SIPC** | npp+0xc000 | **0x921cc000** | 0x73000 | **CPU↔fabric bridge enable** (`pon_npp_sipc_init`: =0x11) |
| **SMCT** | npp+0x10000 | **0x921d0000** | 0x74000 | **CPU-port multi-channel transfer** (`pon_npp_smct_init`: =0xb, +0x10=0x3810) |
| TM rings | tm+0x10050/60 | 0x921d0050/60 | — | UP/DN desc-ring bases — **live inside the SMCT window** |
| QMG | — | 0x9234c000 | 0xd3000 | sw_fwd counter @ +0x44 (reg_id6, mode1 RO) |
| SOPC | — | 0x921d9000 | 0x76400 | send2smac2 @ +0x164 |

**Key reframing:** the registers the corpus calls "the TM UP/DN ring"
(0x921d0054 kick, 0x921d0064 kick) sit at SMCT_base(0x921d0000)+0x54/+0x64.
SMCT = the CPU-port transfer engine. SIPC (0x921cc000) is its enable/bridge
layer with `sipc_set_rx_en` (reg0 bit0) and `sipc_set_cpu_up_en` (reg1 bit2).
**No oracle has ever read the 0x921cc000 (SIPC) window or the SMCT control/FIFO
regs (0x921d0000..0x921d0050) during egress** — only the +0x54/+0x64 desc
kicks. The live note in `stock_live_egress_oracle_re.md:104` even flags a
"separate live block at 0x921cc0xx … HW-dynamic queue state" that was never
probed.

`tm_switch_statistics` (tm:46560-46658) confirms the egress pipeline order and
that QMG sw_fwd is an EGRESS-direction counter (it is dumped between `cla
fwd/trap` and `DSCH in/out que` → `sopc_send2smacN` → `smacN send total`):
```
... sipc_2spa sop/eop ... cla fwd/trap/copy ... QMG sw fwd (0xd3011) ...
DSCH in/out que ... sopc_send2smac0..4 (0x76457+) ... smacN send total
```
So the live reply genuinely flows SIPC/SPA → CLA → QMG sw_fwd → DSCH → SOPC →
MAC2, and the CPU put it there WITHOUT the SMCT desc-ring kick. The most
probable injector is a **SIPC/SMCT FIFO or a DRAM-resident SMCT channel whose
head/tail are in DRAM (polled), not the +0x54/+0x64 MMIO doorbell.**

---

## Concrete next test (do this BEFORE any more code changes)

Re-run the live egress oracle (host `ping -c 300 -i 0.02 192.168.1.1`,
corrected /proc/kmsg persistent-cat + throwaway-first-read + double-read
method) but read the **never-probed SIPC + SMCT windows**, not the ring kicks:

```
# SIPC bridge (0x921cc000) — full block, look for a head/tail that ticks
fpga -r 0x73000 1   # SIPC ctrl (init=0x11)        phys 0x921cc000
fpga -r 0x73001 1   #                              phys 0x921cc004
... sweep 0x73000..0x7300f (0x921cc000..0x921cc03c)
# SMCT control/FIFO (0x921d0000), NOT the +0x54/+0x64 desc kicks
fpga -r 0x74000 1   # SMCT ctrl (init=0xb)          phys 0x921d0000
fpga -r 0x74001 1
fpga -r 0x74004 1   # SMCT +0x10 (init=0x3810)      phys 0x921d0010
... sweep 0x74000..0x74013 (0x921d0000..0x921d004c, i.e. up to the ring base)
# controls
fpga -r 0xd3011 1   # QMG sw_fwd (egress confirm)   phys 0x9234c044
fpga -r 0xa01c6 1   # MAC2 TX-OK (egress confirm)   phys 0x92280718
```
**Predict:** one register in the 0x921cc000 (SIPC) or 0x921d0000..0x921d004c
(SMCT, below the desc-ring at +0x50) range will tick in lock-step with sw_fwd /
MAC2 TX-OK — that is the real ring-less CPU inject doorbell/queue-head. If the
whole SIPC+SMCT-control sweep is ALSO flat, the inject is a DRAM-only queue
(head/tail in DRAM polled by the fabric) and the next move is a DRAM diff of the
SMCT channel region (bases set by `pon_npp_smct_init`) idle-vs-egressing.

Cheap parallel poke (mainline side): the corpus shows mainline never touches
SIPC (0x921cc000) — verify mainline writes `pon_npp_sipc_init`'s `0x921cc000=0x11`
and `pon_npp_smct_init`'s `0x921d0000=0xb` / `0x921d0010=0x3810`. If SIPC
cpu_up_en (reg1 bit2, 0x921cc000 bit2) is unset in mainline, the CPU-port
fabric inject would be disabled regardless of which ring mainline kicks —
plausibly why mainline's frame "dies before QMG" even on the IDM path.

---

## Honest status / confidence
- HIGH: it is NOT the TM UP/DN rings, NOT the IDM ring, NOT per-frame BMU
  alloc, NOT FFE/L3-hardfast (routed-only), NOT a `pon_tm_data_raw_send`
  execution. The decomp's visible SW-TX path is genuinely not what runs.
- MEDIUM: the inject is the SIPC/SMCT CPU-port channel (newly mapped; bases and
  enables confirmed from decomp+reg-tables, but the per-frame doorbell/FIFO
  register is NOT pinned — the SMCT reg table exposes only 3 config regs, and
  the FFE/SMCT data-mover bodies are halt_baddata stubs in this decomp).
- This is partial progress, as the task allows: I converted "unidentified
  ring-less inject" into "the inject is in the SIPC(0x921cc000)/SMCT(0x921d0000)
  CPU-port channel that no live oracle has ever read," with a concrete sweep to
  confirm it.
