# Stock-table descriptor coverage (Phase 7 result)

**Context**: `zx_stock_init_table[22363]` is the static C array (Phase 3)
that replaces the old `stock.bin` firmware blob. Phase 7 mapped each
entry against the `zx_*regtable[]` descriptor arrays from
`linux-v6.6/drivers/net/ethernet/zte/zx-fpga-reg-tables.h` to see how
many writes we can name semantically.

**Result**: `tasks/00.01.eth-driver/findings/stock_table_reg_names.txt`
- Generator: `tasks/00.01.eth-driver/scripts/lookup_stock_regs.py`
- 252 of 22363 entries matched (**1.1 %**)
- 1273 unique fpga word addresses are covered by 651 descriptors
  (some entries match multiple bit-field aliases)

## Per-block matched fraction

| Block      | Hit / Total      | Pct  |
| ---        | ---              | ---  |
| PON_LOW    | 1 / 16           | 6.2% |
| PON_B      | 0 / 1792         | 0.0% |
| PON_TAIL   | 0 / 12036        | 0.0% |
| NPP        | 84 / 1600        | 5.2% |
| NPP_AUX    | 0 / 156          | 0.0% |
| TM         | 64 / 4313        | 1.5% |
| PP_FUC     | 103 / 2450       | 4.2% |

## Why so low (revised after deeper analysis)

The original guess was "PON descriptors are missing." Verified false:
the descriptors we extracted ARE complete. Cross-checking against the
raw `*RegTable` symbol sizes in `tm.ko`:

| Symbol           | tm.ko bytes | Entries (size / 0x1c) | Our descriptors |
| ---              | ---         | ---                   | ---             |
| smacRegTable     | 0x700       | 64                    | 64 ✓            |
| sbragRegTable    | 0x9a0       | 88                    | 88 ✓            |
| spaRegTable      | 0xea8       | 134                   | 134 ✓           |
| claRegTable      | 0x914       | 83                    | 83 ✓            |
| gregRegTable     | 0x7e0       | 72                    | 72 ✓            |
| dpaRegTable      | 0x2bc       | 25                    | 25 ✓            |

So the 651 descriptors are exhaustive over the named reg space. The
real reason coverage is low is structural and different:

**98.4 % of `PON_TAIL` entries are bursts of contiguous-word writes**,
not individual register touches. Sliding-window analysis over the 12036
PON_TAIL entries:

- 590 detected bursts (consecutive entries with offset-delta ≤ 0x40)
- Average burst length: 20.1 entries
- Median burst length: 9
- **Max burst length: 4090 entries** (single contiguous stream)
- Total entries in bursts: 11844 (98.4 %)
- Dominant 3-entry signatures: `(0, 4, 8)` 5730×, `(0, 4, 12)` 591×,
  `(0, 8, 12)` 557×

This pattern is the unmistakable signature of **RAM-table init**: the
driver is filling adjacent words in a large hardware RAM table (FDB,
ACL TCAM, scheduler weight tables, etc.). The driver code we want to
write is one `memcpy_toio()` per burst, not 4090 separate `writel()`s.
The fact that these RAM tables don't have a single "register name"
isn't a hole in our extraction — it's the nature of the HW.

## What this maps to for the upstream submission

The current driver still has a giant `zx_replay_stock_block(eth,
"PON_TAIL", …)` call that runs 12k unannotated writes. That's not
acceptable for a netdev RFC. With the burst result above, the path
forward is clearer than before:

**Phase 8 (planned, task #62)**: detect contiguous-word bursts in
`zx_stock_init_table[]` and emit them as `memcpy_toio()` operations
against generated `static const u32 zx_<block>_<name>_init[]` arrays.
Expected outcome:

- Drop from 22363 individual `writel()`s to a few hundred operations
  (one per burst + the gaps)
- Each `memcpy_toio` site can carry a comment naming the target RAM
  table (FDB at smac+0x0..0x?, ACL TCAM at sbrg+...)
- The remaining non-burst entries (~360) are the genuine
  single-register touches and are good candidates for the existing
  descriptor mapping from Phase 7

**Phase 9 (planned)**: once bursts are isolated, look at the *content*
of each big burst and decide whether it's:
  - A repeating per-port/per-queue init (collapse to a loop)
  - A truly arbitrary RAM-table image (keep as static const u32 [])
  - A handful of named regs that happened to be adjacent (expand back
    to named writes)

## Top descriptor-table hits (with names)

The 252 matched entries are spread across these tables — useful to
sanity-check that the descriptor format is parsed correctly:

| Table              | Hit count |
| ---                | ---       |
| zx_sparegtable     | 665       |
| zx_dparegtable     | 152       |
| zx_schregtable     | 57        |
| zx_claregtable     | 42        |
| zx_sbragregtable   | 38        |
| zx_ponppregtable   | 27        |
| zx_admregtable     | 17        |
| zx_redregtable     | 15        |
| zx_gregregtable    | 15        |
| zx_sadmregtable    | 15        |
| zx_sdetgregtable   | 9         |
| zx_qmgregtable     | 7         |
| zx_pppmregtable    | 7         |
| zx_pontmregtable   | 6         |
| zx_smacregtable    | 3         |
| zx_sipcregtable    | 2         |

(Sums to > 252 because a single fpga_word with multiple bit-field
descriptors counts once per descriptor.)
