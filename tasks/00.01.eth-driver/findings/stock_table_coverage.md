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

## Why so low

Two structural reasons, both fixable:

1. **PON descriptors are missing.** The 651 descriptors in
   `zx-fpga-reg-tables.h` were extracted predominantly from the NPP/TM/PP
   side .ko files. The PON side (smac, sbrg, dpa, sda, sipc, sdet) has
   only a handful of descriptors — 3 from `zx_smacregtable`, 2 from
   `zx_sipcregtable`. The 12036 `PON_TAIL` writes therefore look opaque
   even though many of them are well-named regs inside their `.ko`
   functions; we just haven't pulled the metadata over.

2. **A lot of stock.bin is RAM-table programming**, not direct MMIO
   register writes. The classic stock pattern is "write 2 control regs
   to set up an indirect access, then poll, then write/read a data
   reg" — see `tasks/00.10.02.re-stock-kmods/findings/` for several
   examples. A single semantic operation (`smac_set_fdb_entry(idx, …)`)
   shows up as 4-6 contiguous entries with totally different offsets.
   Even after Phase 8 broadens the descriptor pool, these will still
   read as `UNKNOWN` because they're not regs in the normal sense —
   they're indirect-access protocols.

## What this maps to for the upstream submission

The current driver still has a giant `zx_replay_stock_block(eth,
"PON_TAIL", …)` call that runs 12k unannotated writes. That's not
acceptable for a netdev RFC. Two paths, complementary:

1. **Phase 8 (planned)**: extend the descriptor extraction over the
   PON-side .ko's. Goal: bring `zx_smacregtable`, `zx_sbragregtable`,
   `zx_dparegtable`, `zx_sdaregtable`, `zx_sdetgregtable`,
   `zx_sipcregtable` up to ~real coverage (currently each has <10
   regs). Expected lift: PON_TAIL coverage from 0% to maybe 20-30%
   for direct-MMIO regs.

2. **Phase 9 (planned)**: recognize indirect-access sequences and
   collapse them into helper-function calls like
   `zx_pon_fdb_write(eth, idx, …)`. This converts ~thousands of writes
   from "anonymous data" into named operations even though the raw
   regs underneath stay unnamed.

The order matters: Phase 8 first (it tells us which regs we already
know), then Phase 9 (we use the leftover unnamed clusters as
candidates for indirect-access sequences).

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
