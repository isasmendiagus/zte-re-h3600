# Phase 6 — stock SPA classify rules (matchram + hashram) extracted from tm.ko binary

GROUND-TRUTH (extracted from the tm.ko binary .rodata, byte-identical across 2 builds; NOT inferred):
ext/rootfs/kmodule/tm.ko (.rodata matchram +0x1990 / hashram +0x1af0). Source: tm_pon_npp_spa_initial
(decomp tm.c:43271-43371; binary 0x3ed1c). This is the SPA per-packet classify that emits the
forward-vs-trap action upstream of the CLA hash — the current best lead for the L3 forward gate
(mainline's SPA classify RAMs read all-zero; match_mode=1 but rule-less).

## Indirect-write iface (NPP-relative off = phys-0x921c0000; e->base=0x921c0000)
- status 0x14018 (phys 0x921d4018): poll bit0==1 (idle) before each op
- cmd    0x14014 (phys 0x921d4014): val = addr | (ram_id<<22) | (rw<<27); rw=0=write
- data   0x1401c (phys 0x921d401c): per data_id (STRUCTURAL UNKNOWN: how data_id 0..5 maps to the
  reg — likely 0x1401c + data_id*4, OR an id field; VERIFY against the driver's CLA indirect helper
  zx-eth-main.c ~2011/2049 which does the analogous data-word addressing)
- matchram ram_id=0 (11 rules, packed 4-per-bank by rule>>2 / rule&3, 6 data words/bank RMW —
  on a zeroed mainline RAM just write all 6 words/bank directly); hashram ram_id=5 (8 slots, 2 words:
  data_id=1 <- word1, then data_id=0 <- word0)

## MATCHRAM — 11 entries [rule, valid, v4v6, offmode, offset, cmp, mask, data]
0:  off=0x04 mask=0x00ff data=0x0011  (IP proto UDP)
1:  off=0x0b mask=0xffff data=0x0208
2:  off=0x0b mask=0xffff data=0x076c
3:  off=0x0b cmp=1 mask=0xffff data=0x013e
4:  off=0x0b cmp=2 mask=0xffff data=0x0141
5:  off=0x0a mask=0xffff data=0x0043  (DHCP)
6:  off=0x0a mask=0xffff data=0x0044  (DHCP)
7:  off=0x0b mask=0xffff data=0x0043
8:  off=0x0b mask=0xffff data=0x0044
9:  off=0x04 mask=0x00ff data=0x0006  (IP proto TCP)
10: off=0x0b mask=0xffff data=0x00b3
(all valid=1, v4v6=1, offmode=2; raw template = 8 u32 LE per entry)

## HASHRAM — 8 entries (data0=data_id0, data1=data_id1) + decoded action/valid
slot0: 0x000016a9 0x1aa50200  action=0x2a valid=1
slot1: 0x00001aa5 0x328d0200  action=0x29 valid=1
slot2: 0x0000328d 0x62750200  action=0x23 valid=1
slot3: 0x00026275 0xa2750200  action=0x1d valid=1
slot4: 0x0001a275 0x62750200  action=0x1d valid=1
slot5: 0x00016275 0xa2750200  action=0x1d valid=1
slot6: 0x0002a275 0x20a10200  action=0x1d valid=1
slot7: 0x000c20a1 0x????0200  action=0x28 valid=1   (data1 hi16 = READ-LIVE; static src 2B short)
action = ((byte1&1)<<6)|(byte0>>2); valid = bit1 of byte5. All 8 valid, actions nonzero (0x1d dominant).
The numeric action->forward/trap meaning is consumed DOWNSTREAM (not in this fn) — VERIFY by port+test.

## Port plan (zx_spa_classify_init, called from zx_pm_spa_init near match_mode write @zx-eth-main.c:5301)
1. Resolve the data_id->reg mapping (the one structural unknown) from the driver's CLA indirect helper.
2. matchram: pack the 11 rules into 3 banks (rules 0-3,4-7,8-10), write 6 words/bank (clean-boot = no RMW).
3. hashram: per slot, write data_id1 then data_id0, then cmd (rw=0,ram_id=5,slot). slot7 data1 hi16 read-live.
4. boot + re-run the L3-routed flow + read hw_trap / CLA fwd. CAVEAT: best lead but UNPROVEN (prior
   candidates all HW-refuted) — port-and-test, do not assume.

## UPDATE 2026-06-05 — port-safety RESOLVED; SPA indirect DATA-PORT addressing = open structural unknown
★ CRITICAL SAFETY RESOLUTION: the driver's zx_sch_indirect_write uses 0x14014 too, but via tm_write
(= e->base + TM_OFF 0x180000 + off = phys 0x92354014, the SCH/scheduler port). The SPA classify
indirect (npp_write, phys 0x921d4014) is a DIFFERENT physical register. So porting the SPA classify with
ram_id 0/5 does NOT collide with the SCH (ram_id 5 there = tcont-fill at 0x92354014, unrelated). Porting
is SAFE — won't corrupt egress/QoS. (This conflict, if real, would have broken the scheduler.)
OPEN: the SPA indirect DATA-port addressing (how spa_set_indirect_rw_data(data_id,value) maps data_id
0..5 to a register). Live round-trip tests on mainline (poke, phys 0x921d4014 cmd / 0x921d401c data):
- data_id N at 0x1401c + N*4 → only data_id 0 (0x1401c) round-trips; 0x14020+ read 0. WRONG.
- FIFO (all 6 words to 0x1401c sequentially, then read 6×) → all reads return the LAST word
  (0x66666666). So 0x1401c is a single 1-word reg, NOT a FIFO, NOT auto-incrementing.
⇒ neither obvious pattern. The data_id→reg mapping must be read from spaRegTable[6] (base_off + the
data_id stride/multiplier) in the tm.ko binary — tmOnuRegWrite(6,val,data_id) computes
reg = tbl[6].stride*data_id + tbl[6].base (decomp tmOnuRegWrite). NEXT SESSION: objdump spaRegTable[6]
(and [4]=cmd,[5]=status) from tm.ko to get the exact base+stride, THEN the matchram-bank write works.
The matchram bit-packing (4 cases on rule&3, decomp tm.c:26206-26248) is decoded but not yet ported.
STATUS: SPA-classify-rules-empty remains the best lead for the upstream forward-gate, the port is
proven SAFE, the rules are extracted — blocked only on the data-port addressing (a bounded binary read).
(Live mainline matchram bank0 left with test junk; reboot restores.)

## ★ UPDATE 2026-06-05 — DATA-PORT RESOLVED (round-trip confirmed); SPA classify port fully unblocked
zx_sparegtable (driver zx-fpga-reg-tables.h:629) reg_id 6 (data): base_off 0x75007, stride 1,
max_sub_idx 6 → data_id N at phys 0x921d401c + N*4 (= 0x1401c+N*4 NPP-rel). reg_id 4 (cmd) 0x75005=
0x921d4014, reg_id 5 (status) 0x75006=0x921d4018. My earlier "addressing failed" was an ORDER bug
(extra cmd-write). CLEAN round-trip on mainline (poke) CONFIRMS the protocol + addressing:
  WRITE: cmd(0x921d4014 = addr|ram_id<<22|0<<27)  THEN  data_id 0..5 at 0x921d401c+N*4
  READ:  cmd(0x921d4014 = addr|ram_id<<22|1<<27)  THEN  read 0x921d401c+N*4
  → wrote 0x11/0x22/.../0x66 to data_id0..5, read back 0x11111111,0x22222222,0x33333333,0x44444444,
    0x55555555,0x00066666 (data_id5 top bits truncated = the matchram bank is <192 bits wide). 5/6
    exact = addressing + protocol PROVEN.
⇒ ALL structural unknowns resolved: port-safe (SPA 0x921d4014 ≠ SCH 0x92354014), data-port =
0x1401c+N*4, cmd-first protocol, matchram ram_id=0 / hashram ram_id=5, rules extracted (this file),
matchram packing decoded (tm.c:26206-26248). REMAINING = pure implementation: replicate the matchram
4-case bit-packing (compute the 3 banks from the 11 rules), then load matchram(banks) + hashram(8 slots)
via the indirect iface, in zx_spa_classify_init() (driver) OR live-poke, readback-verify, test the
routed flow (hw_trap / CLA fwd). Hypothesis (SPA-classify = the L3 forward gate) still UNPROVEN until
the port-and-test — but now it's a clean implementation task, not blocked on any unknown.

## ★ UPDATE 2026-06-05 — SPA classify LOADED on mainline, readback OK, but NO forward (6th candidate refuted)
Computed the 3 matchram banks (best-effort packing replication, cases 2/3 low-confidence) + 8 hashram
slots; loaded via the indirect iface on mainline; matchram bank readback = computed words EXACTLY (the
writes landed). Then the routed flow: CLA_fwd[0x9238c3c0]=0 (delta 0), hw_trap +80 — STILL TRAPS.
⇒ loading the SPA classify rules does NOT enable the L3 forward. AMBIGUOUS root (matchram packing
cases 2/3 may be wrong, OR the SPA classify hashram action isn't the L3-forward gate) — but after 6
HW-refuted candidates the SPA-classify hypothesis is weak.

## META-CONCLUSION (static-RE-candidate approach exhausted)
On mainline, EVERY candidate loaded/tested produces the SAME result: hw_trap climbs (traps 100%),
CLA fwd=0. Candidates HW-refuted this arc: (1) CLA config regs (==stock), (2) outspace/MTU, (3) config
bit11, (4) match_mode (already on), (5) ram2 entry at all 520 buckets, (6) SPA classify matchram+hashram.
The extract chain (ram0/ram1 FFE init) + the full hash path are built/validated but never reached.
The static-decomp-candidate method has hit its limit — guessing registers/tables and HW-testing keeps
failing because the actual forward path isn't being localized.
DEFINITIVE methods left (all fresh-session, deeper): (a) kotrace stock DURING a live forward to capture
the actual per-packet forward decision/path (blocked-ish: boot-init not catchable, but the dynamic FFE
install path IS — re-trace what stock writes when a flow starts forwarding, beyond cla_set_hash_table);
(b) test whether stock's CLA fwd counter even climbs during forward (if it stays 0, the offload bypasses
the CLA→QMG path entirely per Iter O, and L3 routing forwards via SBRAG (sbrg_add_ipv4table, base
0x92388000) — a DIFFERENT table we have NOT targeted); (c) full ingress-region reg diff stock-vs-mainline
via the indirect-read recipe (SPA range needs indirect reads, not fpga -r). Lead (b) is the highest-value
re-frame: we may have targeted the wrong forward table (CLA hash) for L3 ROUTING all along.
