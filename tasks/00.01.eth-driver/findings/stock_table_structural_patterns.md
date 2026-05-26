# Structural patterns in the stock-init blob

Discovered while refactoring `zx_stock_init_table[]` (#38 Phase 7-9).
Each pattern is interesting because it lets us collapse N anonymous
writes into one line of meaningful C — and the structure itself
reveals something about the HW.

## Pattern A — PON sub-block layout (Phase 9a)

The first 16 writes in stock.bin are 4 identical quartets at pon_early
offsets 0x00000, 0x10000, 0x20000, 0x30000:

```
+0x0 = 0xffffffff   /* clear/enable bank A */
+0x4 = 0xffffffff   /* clear/enable bank B */
+0x8 = 0xffffffff   /* clear/enable bank C */
+0xc = 0x00044bef   /* sub-block cfg */
```

This is **the first piece of concrete PON memory-map RE we've extracted
from stock.bin** without going through Ghidra. It tells us there are
**4 PON sub-blocks at pon_early stride 0x10000**. Whatever block this
is (smac? sbrg? dpa? — TBD), it has 4 instances and they all need the
same init.

Implemented as `zx_pon_low_init()` (Phase 9a).

## Pattern B — TM per-instance 256-byte table replicated 16 times

In the TM block (driver-offset 0x180000..0x1c0000), there are **16
identical 64-entry bursts**, one per TM instance, at offsets
`0x190240 + i * 0x400` for i in 0..15.

Verified: all 16 instances are **bit-identical** (64/64 positions match
between bursts 0 and 1).

```
TM instance i base: e->base + 0x180000 + i * 0x400
This table:         TM[i] + 0x10240   ←  0x100 bytes
First 4 vals:       0x4ffeff10, 0x4ec33b10, 0x4ec33b90, 0x4ffeff20
Last 4 vals:        0x28, 0x21, 0x28, 0x21
```

(Note: 0x190240 - 0x180000 = 0x10240 from each TM instance base. So
the "+0x10240" suggests this could be a CONFIG region inside each
TM instance.)

Why this matters:
- Collapses **1024 individual writes → 16 `__iowrite32_copy()`** calls
  using one shared source array.
- Confirms TM has 16 instances (we already knew via TM_NUM_INSTANCES,
  but this is independent evidence).
- The values look structured: high half of first 3 words is
  0x4ffeff / 0x4ec33b / 0x4ec33b → these are addresses or pointers
  (looks like 0x4ec00000-region DDR pointers — bppe / bp / rxdesc-ish).
  Actually 0x4ffeff10 is a DDR address — likely a default queue
  base or buffer-ring head. **Worth tracing during stock boot to
  confirm.**

Implementation candidate: `zx_tm_per_instance_table_init()` in Phase 9d.

## Pattern C — 4080 identical writes + 2 outliers (the 16 KB bulk init)

The single biggest burst in stock.bin (4082 entries, ~16 KB) at
pon_early off=-0xfffc0 (HW addr 0x920c0040) is mostly **one repeated
value with two specific overrides at the end**:

```
4080 entries × 0x00004bef       ←  default value for entries 0..4079
        1 entry × 0x07d0000c    ←  outlier at idx 4080
        1 entry × 0x0000002a    ←  outlier at idx 4081
```

This is a 4082-entry RAM table being initialized to a default
value 0x4bef, with the LAST TWO entries overridden. Reading it that
way:

- The RAM table has 4082 entries × 4 bytes = 16,328 bytes
- 4080 entries get the same default → `__memset_io` would do it
  even cheaper than the burst we have now
- Two specific entries (4080 and 4081) get configured values
- Those last two suggest the table has a "control" footer:
  index 4080 = 0x07d0000c looks like a counter/threshold word
  (0x7d0 = 2000 decimal — plausible as a max-credits or threshold)
  index 4081 = 0x2a = 42 → could be an instance count or feature
  bitmask

Pattern: **{0x4bef × N} + {one threshold word, one count word}**.
This is the classic signature of a HW RAM table that holds N
"slots" with a fixed default, followed by a small control header.
Possible candidates: an IP-MAC or VID lookup with a default
"unknown → drop with code 0x4bef" entry, or an ACL TCAM init
where 0x4bef is the default action.

0x4bef = 0b 0100_1011_1110_1111. Notable subfields:
- bits 0..3 = 0xf (commonly: rate-limit/credit max)
- bits 4..15 = 0x4be (commonly: 1214 — close to MTU 1500 ÷ 1.23?
  or 1214 decimal could be a packet-length cap)
- top half = 0 → these are 16-bit fields, the rest is reserved

Implementation candidate: `zx_pon_lookup_table_init()` with
`memset_io(off, 0xef, …)` + the 2 footer writes. Phase 9e.

## Pattern D — PON_B has zero bursts (1792 scattered singletons)

In contrast to PON_TAIL, the entire PON_B block (driver-offset
-0x180000..-0x140000, 1792 entries) has **zero +4-stride runs**.
Every write is to a different non-adjacent offset.

Implication: PON_B is **all control registers**, not RAM tables.
Each write is a meaningful, named register. This is the block
that would benefit MOST from descriptor-table naming (Phase 7) —
but the existing 651 descriptors covered 0 % of these because they
target the PON-side .ko's that don't expose their reg tables to
tm.ko's *RegTable symbols.

For PON_B, the right RE path is:
1. Pull function decompilations from `decomp_all_zx_ponreg.c`
   and the other PON .ko's
2. Match each driver-offset to the function that writes it
3. Then we can refactor PON_B into `zx_smac_init() + zx_sbrg_init()
   + zx_dpa_init() + …`

That's much more labor-intensive than Patterns A/B/C and is the
right job for an extension to `kotrace` — record (function, write
offset, value) tuples during a stock boot.

## What would make all four EVEN faster

The bottleneck for B and C is **knowing what the table is for**. We
can collapse the writes mechanically right now, but naming the helper
function (`zx_tm_per_instance_table_init` → `zx_tm_credit_init` or
similar) needs domain knowledge from the .ko side.

The fastest unblock would be:
- Run **kotrace** on stock during init with hooks on the relevant
  `*_init()` functions (PonTmInit, smacInit, etc.) and have it dump
  the stack trace + register args around each write.
- Match the offsets of writes captured by kotrace against our static
  table → automatic naming.

This is the "extender el stockport" path the user has been mentioning.
