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
