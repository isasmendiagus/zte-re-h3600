# DN-ring → DSCH drain: the missing downstream scheduler config (RE, static/decomp) — 2026-05-28

Investigation only. Question: what does stock configure for the DOWNSTREAM (DN) scheduling
path that makes DN-ring / DN-QMG frames DRAIN (DSCH → QMG → SOPC), which mainline lacks?

Addressing model (cross-checked, NOT just decomp-inferred):
- `e->base = 0x921c0000`, `tm_base = 0x92340000`, driver `TM_OFF = 0x180000` so
  `tm_write(off) → 0x92340000+off`. SchRegTable/QmgRegTable `base_off` is a DWORD index from
  `0x92000000` (phys = `base_off*4`).
- VERIFIED: QMG `base_off 0xd3011*4 = 0x9234c044` == the known-good "sw_fwd" counter; SCH
  `base_off 0xd5000*4 = 0x92354000` == `tm[0x14000]`. Both match `tm_base+0xc000`/`+0x14000`.

## KEY RECLASSIFICATION (resolves the apparent contradiction)
`qmg_get_statistics` (decomp_all_tm.c:33061-33073) reads QmgRegTable reg_ids and labels them:
- reg_id 6 = **0xd3011 = 0x9234c044 = "qmg DN sw fwd pkt"** ← the counter every oracle watched
- reg_id 9 = 0xd3015 = 0x9234c054 = "qmg UP sw fwd pkt"
So the "QMG sw_fwd" at 0x9234c044 is specifically the **DOWNSTREAM** QMG sw-forward counter
(pipeline_counter_map.md mislabeled it generic). CPU→LAN egress is downstream → DN-QMG-sw-fwd
is the correct counter, and the drop downstream of it (drop_DSCH) is the **downstream
scheduler** dropping. This is fully self-consistent.

## THE GAP: mainline programs only the UPSTREAM shaper RAM; the DOWNSTREAM RAM stays 0
The SCH block (tm[0x14000], phys 0x92354000) is one HW scheduler with **separate UP and DN
indirect-RAM tables**, selected by RAMID in the indirect CMD
(`cmd = RAMAddr | RAMID<<22 | indRwEn<<27 | incrEn<<31`, `sch_set_indirect_rw_cmd` @29690;
RAMID valid 0..0xf). Enumerated every RAMID by its setter:

| RAMID | setter | dir | mainline `zx_sch_init` programs? |
|------|--------|-----|------|
| 2 | sch_set_up_pq_sharp_fill_rate @30482 | UP | YES |
| 3 | sch_set_up_pq_sharp_bucket_cap @30648 | UP | YES |
| 5 | sch_set_up_tcont_sharp_fill_rate @30808 | UP | YES |
| 6 | sch_set_up_tcont_sharp_bucket_cap @30955 | UP | YES |
| 0xb | sch_set_dn_que_sp_dwrr_cfg @31929/70 | **DN** | **NO** |
| 0xc | sch_set_dn_queue_wrr_weight @32146 | **DN** | **NO** |
| 0xe | sch_set_dn_tcont_sharp_fill_rate @32357/66 | **DN** | **NO** |
| 0xf | sch_set_dn_tcont_sharp_bucket_cap @32525 | **DN** | **NO** |

Mainline `zx_sch_init` (zx-eth-main.c:2574-2597) loops 0x20 units × 8 queues writing ONLY
RAMID 2/3/5/6. This replays stock `tm_pon_tm_sch_initial` (tm.c:47025) faithfully — but that
stock fn ALSO only programs the UP path (it calls `tm_tcont_que_sharp_set`@45535 →
`sch_set_up_*`, and `tm_tcont_sharp_set`@45564 → `sch_set_up_*`). **The DOWNSTREAM tcont
shaper is NEVER programmed by tm.ko init.** It is programmed later by the rootfs QoS layer
(cspd → `tm_port_egress_traffic_sharp_set`@45453 → `sch_set_dn_tcont_sharp_fill_rate/bucket_cap`
RAMID 0xe/0xf, and `tm_port_egress_spdwrr_schedule_set`@36546 → RAMID 0xb/0xc), reached via
the `zte_api_sw_qos_*` entrypoints (tm.c:57181,57190) and the switch.ko port-init path
(`pon_driver_adapter_schedue_mode_set` → `tm_tcont_que_sch_sp_dwwr_mod_set`). Corroborated by
`stock_rootfs_qos_sched_config.md` §5: the DN token-bucket default is fill=cap=**0** = zero
credit; cspd fills it at runtime. Mainline never runs cspd → DN tcont bucket-cap = 0 forever →
the downstream scheduler tcont has zero credit → it can never dequeue → drop_DSCH (exactly the
"fetched-but-never-drained" symptom; mirrors the UP-path bug we already fixed, but on the DN
tables).

Note `sch_set_dn_pq_sharp_fill_rate/bucket_cap` (@32271/32289) are STUBS (`return 0`): the DN
direction has NO per-queue shaper, only per-tcont (RAMID 0xe/0xf, `unit` 0..7 = the 8 LAN
egress tconts) + per-queue SP/DWRR mode (0xb) + WRR weight (0xc). So the DN credit lives ONLY
at tcont level — that is the single thing that must be non-zero to drain.

## Ruled out (already correct in mainline)
- QMG dn_ram_thd: stock `qmg_set_dn_ram_thd(0x1fa0)` + `qmg_set_up_ram_thd(0x50)`
  (tm_pon_tm_qmg_initial @42642, gated on `lan_up==1`) writes QmgRegTable reg0/1 = tm[0xc000]
  bits[12:0]/[25:13]. Mainline link-up writes `tm[0xc000]=0x03f40050` (zx-eth-main.c:4097) =
  up_thd 0x50 | dn_thd 0x1fa0 — EXACT match. Not the gate.
- SCH enable mask: mainline keeps `tm[0x14000]=0x3d7`, which includes bit1 dwrr, bit6
  secsch_dwrr, bit8 hw_dn_age. So the downstream scheduler is ENABLED; only its credit RAM is
  empty. (sch_initial sets bits {0,1,2,4,6,8}=0x157; 0x3d7 is a superset — fine.)

## First poke-test to try (live, [0x921c0000,0x923c0000), SCH indirect port is static config)
Program the DOWNSTREAM tcont shaper credit for all 8 LAN tconts, mirroring the UP fix values
(fill 1600000=0x186A00, cap tm_getFillcap(1600000)=200000=0x30D40). The host/LAN egress tcont
index is unconfirmed (internal port 3 = MAC2 → likely unit 3), so sweep units 0..7.

Indirect port phys: CMD 0x92354014, DONE 0x92354018 (RO bit0=idle), DATA 0x9235401c.
Sequence per write = poll DONE bit0 → write CMD → write DATA (CMD-before-DATA, no trailing
poll), exactly as the stock dn setters. For each unit u in 0..7:
```
# RAMID 0xe = DN tcont fill-rate, addr = u, cmd = u | (0xe<<22) = 0x03800000 | u
poke 0x9235401c 0x00186A00            # data = fill-rate 1600000
poke 0x92354014 (0x03800000 | u)      # cmd: RAMID 0xe, write
# RAMID 0xf = DN tcont bucket-cap, addr = u, cmd = u | (0xf<<22) = 0x03C00000 | u
poke 0x9235401c 0x00030D40            # data = cap 200000 (MUST be non-zero)
poke 0x92354014 (0x03C00000 | u)      # cmd: RAMID 0xf, write
```
(e->base offsets: CMD 0x194014, DONE 0x194018, DATA 0x19401c.)

Predict: with frames reaching DN-QMG-sw-fwd (0x9234c044), drop_DSCH (0x921da04c) STOPS
climbing and DSCH-out-que (0x921941fc) / sopc_send2smac2 (0x921d9164) / MAC2 TX
(0x92280718) start climbing. If it only works for one unit, that unit IS the host tcont.
Optionally also set RAMID 0xb (DN SP/DWRR mode, addr=unit, RMW) to 0 (SP) for that unit if
mode defaults to an invalid state — but try the tcont credit alone first (highest-confidence
single change). If frames still die at DN-QMG-sw-fwd==0 (the NEW symptom in the task: DN ring
fetched but sw_fwd stays 0), that's a DN-DMA→QMG enqueue problem UPSTREAM of DSCH, not the
shaper — separate from this finding.

## Cites
decomp_all_tm.c: 47025 (sch_initial, UP-only), 45535/45564 (up tcont/que sharp set),
45453 (tm_port_egress_traffic_sharp_set → dn RAMID 0xe/0xf), 36546 (spdwrr_schedule_set → dn
RAMID 0xb/0xc), 29690 (indirect cmd encoding), 32271/32289 (dn pq STUBS),
32309/32471 (dn tcont fill/cap, RAMID 0xe/0xf), 31875 (dn que sp/dwrr, RAMID 0xb),
33061-33073 (qmg_get_statistics: 0xd3011 = DN sw fwd), 42624/42642 (qmg_initial dn_ram_thd).
zx-fpga-reg-tables.h:138-158 (SchRegTable), :105-118 (QmgRegTable).
zx-eth-main.c:2574-2597 (zx_sch_init, UP-only), :4097 (QMG ram_thd already correct).
refs/orca-h3600p/.../pon_driver_adapter_schedue_mode_set.c (DN sch mode per tcont/queue).
stock_rootfs_qos_sched_config.md §5 (DN shaper default = 0, filled by cspd at runtime).
