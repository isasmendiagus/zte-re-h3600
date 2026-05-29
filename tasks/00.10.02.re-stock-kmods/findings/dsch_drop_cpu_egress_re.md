# DSCH drops CPU→LAN egress frame — root cause + fix (RE, static/decomp only)

Localization (proven, `pipeline_trace_dies_at_dsch.md`): QMG_sw_fwd +6 →
**drop_DSCH (e->base+0x1a04c, phys 0x921da04c) +6** → SOPC_send2smac2 = 0.
QMG hands the frame to the downstream scheduler; the scheduler DROPS it.

## ROOT CAUSE: mainline never populates the SCH per-queue shaper RAM

The DSCH (TM[0x14000] "SCH" block) is a **token-bucket / SP-DWRR scheduler**.
A queue can only dequeue when its shaper bucket has credit. Per-queue shaper
**fill-rate** and **bucket-capacity** live in *indirect RAM tables*, written via
the SCH indirect-access port — NOT by direct register writes.

The indirect port (SchRegTable, `zx-fpga-reg-tables.h:138`, base 0x000d5000 =
TM[0x14000]):
- id13 `0x000d5005` = TM[**0x14014**] = indirect RW **command** (mask 0x8fcfffff)
- id14 `0x000d5006` = TM[**0x14018**] = ind-acc **done** (RO status)
- id15 `0x000d5007` = TM[**0x1401c**] = ind-acc **data**

Command encoding (`sch_set_indirect_rw_cmd`, tm.c:29690):
`cmd = RAMAddr + RAMID*0x400000 + indRwEn*0x8000000 + incrEn*0x80000000`.

Stock `tm_pon_tm_sch_initial` (tm.c:47025) runs, for 0x20 units × 8 queues:
`tm_tcont_que_sharp_set(unit,que,1600000)` (tm.c:45535/51868) which calls:
- `sch_set_shp_fill_time(0x1869)` → TM[0x14028]   (global)
- `sch_set_spend_byte(0x14)`     → TM[0x14024]     (global)
- `sch_set_up_pq_sharp_fill_rate(unit,que,1600000)` → **RAMID 2**, addr=que+unit*8 (tm.c:30482)
- `sch_set_up_pq_sharp_bucket_cap(unit,que,getFillcap(1600000))` → **RAMID 3**, addr=que+unit*8 (tm.c:30648)
plus per-tcont `tm_tcont_sharp_set` → **RAMID 5** fill-rate + bucket-cap (tm.c:32309).
Each is a poll-done → write-cmd(TM[0x14014]) → write-data(TM[0x1401c]) sequence.

### What mainline does instead (zx-eth-main.c:2583-2595)
```
tm_write(e,0x14014,0x03c00006);  // = SCH indirect CMD reg!  RAMID=(>>22&0xf)=0xF (invalid) → garbage no-op
tm_write(e,0x14018,0x00000001);  // = ind-acc DONE (RO status) — meaningless
tm_write(e,0x1401c,0x0003e800);  // = ind-acc DATA, no valid cmd behind it
tm_write(e,0x14024,0x00000014);  // spend_byte — OK by luck
tm_write(e,0x14028,0x00001869);  // shp_fill_time — OK by luck
```
Mainline got the two **global** scalars right by coincidence but **never executes
a single valid indirect sequence**, so every per-queue shaper RAMID-2 fill-rate
and RAMID-3 bucket-cap entry stays **0**. Bucket cap 0 = zero credit forever →
the DSCH can never dequeue the CPU→LAN(internal port 3 = MAC[2]) queue → it
**drops** the frame (drop_DSCH++). This is the gate.

Corroboration: live diff never even compared this block — `zx_regdump_wins`
(zx-eth-main.c:3599) covers 0x010000 (TM-DMA, dynamic) but **NOT 0x014000**,
so the broken SCH config was never caught. Stock dump confirms 0x14014/18/40
read 0xffffffff (indirect-port semantics, not config words).

## CONCRETE FIX

Replace the 3 bogus direct writes (0x14014/0x14018/0x1401c) with a real
indirect-RAM init that mirrors stock's `tm_pon_tm_sch_initial` per-queue loop.
Minimum to unblock egress: program RAMID-2 (fill-rate) AND RAMID-3 (bucket-cap)
for the unit/queue the CPU→LAN path uses. Internal port 3 = MAC[2] → unit=3.

Helper (one indirect write):
```c
static void sch_ind_write(struct zx_eth *e, u32 ramid, u32 addr, u32 data) {
    int t = 20; while (t-- && !(tm_read(e,0x14018) & 1)) udelay(2);   /* poll done */
    tm_write(e, 0x14014, addr | (ramid<<22));   /* incrEn=0,indRwEn=0(write) */
    tm_write(e, 0x1401c, data);                 /* data */
}
```
Init loop (stock-faithful: 0x20 units × 8 queues, rate 1600000):
```c
for (u=0; u<0x20; u++) for (q=0; q<8; q++) {
    sch_ind_write(e, 2, q + u*8, 1600000);          /* pq fill rate  */
    sch_ind_write(e, 3, q + u*8, 0x186a0 /*cap*/);  /* pq bucket cap */
}
for (u=0; u<0x20; u++) sch_ind_write(e, 5, u, 1600000); /* tcont fill rate */
```
Keep TM[0x14024]=0x14 and TM[0x14028]=0x1869 (already correct).

### POKE-TEST FIRST (live, before source change)
The SCH indirect port is poke-testable (static config, not the dynamic 0xc000
QMG block). phys = 0x921c0000 + off. For the host path unit=3, queue 0:
```
# RAMID2 fill-rate, addr = 0 + 3*8 = 0x18, cmd = 0x18 | (2<<22) = 0x00800018
poke 0x921d401c 0x00186a00     # data = 1600000
poke 0x921d4014 0x00800018     # cmd: RAMID2, addr 0x18, write
# RAMID3 bucket-cap, cmd = 0x18 | (3<<22) = 0x00c00018
poke 0x921d401c 0x000186a0     # data = bucket cap (nonzero)
poke 0x921d4014 0x00c00018     # cmd: RAMID3, addr 0x18, write
```
(Write DATA reg before CMD, matching `sch_set_indirect_rw_cmd` then
`sch_set_ind_acc_data` ordering at tm.c:30482-83.) If the CPU→LAN path uses a
different queue index, sweep q=0..7 at addr 0x18..0x1f. If drop_DSCH stops
incrementing and SOPC_send2smac2 starts climbing, this is confirmed → commit
the full init loop above. If unit≠3, also try units 0..7 (addr u*8).

Cites: tm.c:47025 (sch_initial loop), 45535/51868 (tcont_que_sharp_set),
30420-30490 (pq fill-rate RAMID2), 30586-30656 (pq bucket-cap RAMID3),
32309 (tcont fill-rate RAMID5), 29669-29722 (indirect cmd encoding);
zx-fpga-reg-tables.h:138 (SchRegTable id13/14/15);
zx-eth-main.c:2583-2595 (broken direct writes), :3599 (regdump misses 0x14000).
