# printk_injection_methodology

**Status**: open (tooling not built yet)
**Owner**: -
**Started**: 2026-05-22
**Task IDs**: #103 (build the tool), #104 (first use: chip_tm_init trace)
**Updated**: 2026-05-22

## Question

How do we add `printk` calls to a stock `.ko` binary without source code,
load it on the stock device, and observe the output?

This is **the** RE methodology for this project, because:
- Stock kernel built with `# CONFIG_KPROBES is not set` → can't trace at runtime
- Stock kernel built with `# CONFIG_FUNCTION_TRACER is not set` → no ftrace
- Source not available (no GPL release from ZTE/Digi despite request)
- We DO have UART output on stock now via `kmsg2uart` daemon (see `tasks/00.02.stock-shell/`)

So the workflow is: binary-patch `.ko` → push to device → `rmmod`+`insmod` →
trigger code path → read UART → study.

## Why we care

Every open `rx_path_dead` sub-question (#87, #89, #90, #91, #92, #93)
needs this. Without it we're brute-replaying register dumps without
understanding what stock actually DOES. With it, we can ask the stock
driver "what register did you write here? what value? in what order?"
and just port the answers.

## Hypotheses (most likely first)

1. **ELF splicing on a placeholder NOP**: identify free space at end of
   `.text` or `.init.text` in the `.ko`, write a printk-thunk there, patch
   one branch at the observation point to jump to it. Thunk saves regs,
   loads fmt string, calls printk, restores regs, branches back.
2. **Use an existing function trampoline**: some `.ko`s have unused
   debug-print helpers compiled in. Easier to repurpose than to splice.
3. **Module-init hook**: easiest target — patch `init_module` entry to
   call printk first, then jump to original code. Tells us when module
   loads but not what its internal functions do.

## What I've tried

| Date | Experiment | Result | Note |
|------|-----------|--------|------|
| (earlier) | Found `auto_patch_plat.py` in `tasks/99.01.linux-stockport/` | Has ARM-relocation-aware splicing pattern | recycle as basis for the new tool |
| 2026-05-22 | Documented the methodology | This file | tool not built yet |

## Open sub-questions

- [ ] Where exactly is the free space in each stock `.ko` for the thunk?
      (must not collide with relocations)
- [ ] How does ARM module loader resolve `printk` symbol? We need to add a
      relocation entry pointing at the kernel's printk export.
- [ ] Format string lives in `.rodata` — can we expand `.rodata` in-place,
      or do we need to append a new section?
- [ ] How big can the thunk be? (size of save-regs + load-fmt + bl printk +
      restore-regs in ARM = ~32 bytes)

## Next concrete step

1. Read `tasks/99.01.linux-stockport/auto_patch_plat.py` end-to-end.
2. Extract its ARM splicing pattern into `tools/ko_printk_splice.py` with
   CLI: `--input X.ko --output Y.ko --offset 0xNNNN --fmt 'str' --args r0,r1`.
3. Smoke-test on a tiny `.ko` we own (e.g. our `zx279128-eth.ko`) — add a
   printk at `zx_eth_open`, load on mainline, verify the printk fires.
4. Once smoke test passes, point it at stock `switch.ko` `chip_tm_init`.

## References

- `tasks/99.01.linux-stockport/auto_patch_plat.py` — prior art (the splicing pattern)
- `docs/ITERATE.md` Loop B — the iter cycle this methodology unlocks
- `ROADMAP.md` "Now" step 2 — this is the unblock for step 3 (RX work)
- `LEARNED.md` "How to observe what stock kernel modules do at runtime" —
  high-level summary of why this is the only path
- Related: [[research/rx_path_dead]] (the first customer for this tool)
