# SCH per-queue shaper RAM init — source fix (2026-05-28)

Implements the real SCH indirect-RAM init in the mainline driver, replacing the
three garbage writes to the SCH indirect-access port that left every per-queue
shaper bucket-cap at 0 → DSCH dropped every CPU→LAN egress frame (drop_DSCH++).
See `dsch_drop_cpu_egress_re.md` + `pipeline_trace_dies_at_dsch.md`.

## What changed (linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c)

1. New code inserted just before `zx_tm_dma_init` (now ~line 2498):
   - `#define ZX_SCH_REG_CMD/DONE/DATA` = 0x14014 / 0x14018 / 0x1401c.
   - `zx_sch_wait_done(e)` — polls TM[0x14018] bit0 (done/idle) up to 0x14 tries,
     2us apart. Mirrors `sch_get_ind_acc_done` (decomp_all_tm.c:29725) and the
     ~0x14-try poll loops in the shaper setters.
   - `zx_sch_indirect_write(e, ramid, addr, val)` — does **poll-done → CMD → DATA**
     (CMD before DATA, no trailing poll), exactly as the stock single-value
     setters: `sch_set_up_pq_sharp_fill_rate` @30481-30483,
     `sch_set_up_pq_sharp_bucket_cap` @30647-30649,
     `sch_set_up_tcont_sharp_fill_rate` @30807-30809.
     CMD word = `(addr & 0x1ff) | ((ramid & 0xf) << 22)` (incrEn=0, indRwEn=0=write),
     per `sch_set_indirect_rw_cmd` @29690.
   - `zx_sch_init(e)` — the per-queue replay loop (below).

2. In `zx_tm_dma_init`, the SCH block (was zx-eth-main.c:2588-2595):
   - KEPT: `tm_write(0x14000,0x3d7)`, `0x14004=0x0d1cef00`, `0x14024=0x14`
     (spend_byte), `0x14028=0x1869` (shp_fill_time), `0x14040=0x249`.
   - REPLACED the 3 garbage indirect-port writes (`0x14014=0x03c00006`,
     `0x14018=0x00000001`, `0x1401c=0x0003e800`) with a single `zx_sch_init(e);`.

## Derivation (decomp cites)

Stock `tm_pon_tm_sch_initial` (decomp_all_tm.c:47025) loops:
```
for unit (iVar5) = 0 .. 0x1f          (@47057: != 0x20)      → 0x20 units
  tm_tcont_sharp_set(unit, 1600000)   (@47050)
  for que (iVar4) = 0 .. 7            (@47055: != 8)         → 8 queues
    tm_tcont_que_sharp_set(unit, que, 1600000)  (@47052)
```
plus globals `sch_set_que_sharp_enable(1)`/`dwrr`/`secsch_dwrr`/`tcont_sharp`/
`hw_up_age`/`hw_dn_age` (@47036-47045) — all already covered by the kept
`0x14000=0x3d7` enable mask (bits 0,1,2,4,6,7,8 = que_sharp/dwrr/hw_up_age/
tcont_sharp/secsch_dwrr/oam_age/hw_dn_age; reg_ids confirmed from each
`tmOnuRegWrite(<id>,...,&SchRegTable)`).

`tm_tcont_que_sharp_set` (@45535):
- `sch_set_up_pq_sharp_fill_rate(unit,que,1600000)` → **RAMID 2**, addr=`que+unit*8`, val=1600000 (@30482-30483)
- `sch_set_up_pq_sharp_bucket_cap(unit,que,getFillcap(1600000))` → **RAMID 3**, addr=`que+unit*8` (@30648-30649)

`tm_tcont_sharp_set` (@45564):
- `sch_set_up_tcont_sharp_fill_rate(unit,1600000)` → **RAMID 5**, addr=`unit` (@30808)
- `sch_set_up_tcont_sharp_bucket_cap(unit,getFillcap(1600000))` → **RAMID 6**, addr=`unit` (@30955)

Value formats (raw, NOT packed):
- fill-rate = **1600000 = 0x186A00** (< setter limit 0x200000). Written verbatim.
- bucket-cap = **`tm_getFillcap(1600000)` = 200000 = 0x30D40** (< limit 0x400000).
  Derivation: `tm_getFillcap` (@45355) scans a 10-entry {threshold,cap} table.
  Table extracted from tm.ko .rodata @0x1b60 (objdump): thresholds 128/256/512/
  1024/2048/4096/8192/10240/15360/20480. 1600000 exceeds all 10 → falls to
  `tm_getFillcap_part_44` (@42422): `1600000>>8 = 6250`; 6250 < 199999 →
  returns **200000**. (The legacy poke in dsch_drop_cpu_egress_re.md used cap
  0x186a0 = wrong; the real cap is 0x30D40. Mainly cap must be nonzero, but this
  matches stock exactly.)

RAMID for fill-rate = 2 (per-queue) / 5 (tcont); bucket-cap = 3 (per-queue) /
6 (tcont). RAMID5 = tcont fill-rate (confirms older note). No RAMID4 needed.

## Why the prior live poke failed (per task)

It skipped the done-poll, used DATA-then-CMD order, and used the wrong cap value
(0x186a0). The source fix polls done first, issues CMD-before-DATA, programs ALL
0x20×8 per-queue entries + all tcont entries, and uses the stock cap 0x30D40.

## How to verify (build + reboot + re-trace, per pipeline_trace_dies_at_dsch.md)

1. Build the kernel/driver, flash, reboot. (Caller does this.)
2. dmesg should show: `SCH shaper RAM init: 32 units x 8 queues, rate=1600000 cap=200000`.
3. Re-run the per-stage counter trace (ping the host 6×, diff counters):
   - `drop_DSCH (0x921da04c)` should **stop** incrementing (was d=+6).
   - `SOPC_send2smac2 (0x921d9164)` should now **climb** (was d=0).
   - `SMAC2 / MAC[2] TX (0x92280714..)` should **climb** (was d=0).
   - `QMG_sw_fwd` keeps incrementing as before.
   If drop_DSCH still climbs, sweep: the host path uses internal port 3 = MAC[2]
   = unit 3, queues 0..7 (addr 0x18..0x1f) — already covered by the full loop.
