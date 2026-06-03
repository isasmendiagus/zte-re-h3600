# CLA regport2 (port1) — mainline vs stock vs source-table  (2026-06-01)

Reliable reads: stock via fpga+/dev/logger_main (warmup); mainline via clapeek double-read on a CLEAN
build (reverted source, `CLA init: 1804 ok, 0 fail`). Source = zx_cla_table.h entries 727/731/732.

## ram2 word0 (the classification entry's first word)
| entry (ram2 addr)            | source table | STOCK live | MAINLINE live |
|------------------------------|-------------|-----------|---------------|
| regport2 0x21/0x121/0x221/0x321 | 0x01005055 | 0x01005055 | **0x0100006d** ✗ |
| regport2 0x93/0x193/0x293/0x393 | 0x01005055 | 0x01005055 | **0x0100005d** ✗ |
| regport3 0x79/0xcb/0x179/0x1cb  | 0x01005055 | 0x01005055 | 0x01005055 ✓ |

words 1..5 of every entry MATCH across all three (only word0 differs, only for regport2).

## Conclusion
The SOURCE TABLE is correct (0x01005055 for regport2, = stock). Mainline's CLA replay **silently
corrupts word0 of the regport2 classification entries** (writes 0x006d/0x005d instead of 0x5055) while
regport3 is written correctly — and `CLA init` reports 0 fail (the flaky indirect WRITE corrupts word0
without erroring). This is a port1(regport2)-specific corruption of the CLA classification entry → the
most likely root cause of port1's `drop_PP` (frames not trapped to CPU). 
NOT YET FIXED (stopped here per request). Next: make the CLA replay write reliable (proper commit
handshake / verify-with-RELIABLE-read) so regport2 word0 lands as 0x01005055, then re-test port1.

## ROOT-CAUSE MECHANISM CONFIRMED (2026-06-01) — word0 write-commit race
The `.h` table is CORRECT. The bug is in `zx_cla_write_entry`: each entry's **word0 (data[0]) ends up
holding the NEXT entry's word0**. Proof from the data:
- mainline ram2 addr0x21 read = `0100006d 00154000 80000408 90000817 00000042 000000e0` — words **1..5
  match table entry 727 (regport2) EXACTLY**; only word0 is wrong (`0100006d` vs `01005055`).
- `0x0100006d` is the word0 of the NEXT table entries 728/729 (addr 0x4e/0x55). Likewise regport2 addr
  0x93 (entry 732) reads `0100005d` = word0 of the next entry 733 (addr 0x9f).
Mechanism: data[0] is written first and the indirect CMD commit latches it LATE — after the next
iteration has already overwritten the data[0] register. So every entry's word0 = next entry's word0.
It only produces a WRONG value at word0 "group boundaries":
- entry 727 (regport2, word0 0x5055) is followed by 728 (0x006d) → 727 corrupted → **port1 broken**.
- entry 731 (regport3, 0x5055) is followed by 732 (0x5055) → unchanged → **port2 works by luck**.
This is NOT a read artifact (words 1..5 are entry 727's; only word0 is the neighbor's). It IS the
port1 root cause. FIX (next, not done): make zx_cla_write_entry's commit reliable so data[0] is latched
before the next entry's data[0] write (proper DONE handshake / barrier / re-issue data[0] after CMD),
then re-verify regport2 word0 == 0x01005055 and re-test port1 forwarding.

## ⚠️ RETRACTION (2026-06-01, later) — the word0 "corruption" is UNCONFIRMED (likely a READ artifact)
The write-race fix (readback + udelay in zx_cla_write_entry) was built and tested: **it did NOT change
the read word0 and did NOT fix port1** (still drops at drop_PP, rx_per_ingress port1=0). A controlled
sequence-read then showed the mainline **clapeek word0 (data[0]) read is itself UNRELIABLE**: reading a
known sequence of addrs, word0 does NOT match the source table even for entries that should be correct,
in an address-dependent (non-shift) way — while words 1..16 read fine. So `zx_cla_read_entry`'s data[0]
read returns something stale/wrong on mainline.
⇒ The earlier "mainline regport2 word0 = 0x0100006d (corrupt)" was very likely a clapeek read artifact,
NOT real CLA corruption. The CLA-word0-corruption root-cause claim is RETRACTED/unconfirmed. The fix is
reverted (it fixed nothing). RELIABLE facts unchanged: port1 drops at drop_PP; the stock golden above
was read via fpga (reliable). To make progress on the CLA we'd first need a RELIABLE mainline CLA read
(fix zx_cla_read_entry's data[0] — e.g. dummy/re-read) before trusting ANY mainline word0 value.

## RESOLVED (2026-06-01, final) — clapeek word0 read is OFFSET BY ONE ENTRY; CLA is CORRECT
Tried to fix zx_cla_read_entry (settle udelay + discard) — word0 still read "wrong". But mapping the
reads against the source table cracked it: **read[A].word0 == table[A+1].word0 (next populated entry),
7/7 exact** (e.g. read[0x21]=006d=table[0x4e]; read[0x55]=5055=table[0x79]; read[0x93]=005d=table[0x9f]).
So the clapeek indirect read returns data[1..16] correctly but **word0 shifted by one entry**. ⇒ the
STORED word0 is the table value: regport2 (0x21) true word0 = table[0x21] = **0x01005055** = the stock
golden. **The CLA is correctly programmed and is EXONERATED** — the earlier "regport2 word0 corrupt
(0x006d)" was purely this read offset (stock's fpga read showed the correct 0x01005055 because its CMD
and data reads are ms apart). zx_cla_read_entry left as-is with a NOTE; don't trust its word0 from a
single read. NET: CLA ruled out for real. port1's drop_PP cause remains unidentified.
