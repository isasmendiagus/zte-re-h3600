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

See [`../PLAN_init_debug.md`](../PLAN_init_debug.md) for the phased plan
this methodology executes (Phase 1 = build the splicer).

## Design notes (refined 2026-05-23 during Phase 1 scoping)

### Tier 1 ≠ `.init.text` literally

Inspecting `ext/kmodules_dump/switch.ko` revealed:
- `.init.text` is only **48 bytes** (one function: `init_module`)
- `init_module` is a 12-instruction wrapper that calls `sw_init_switch`,
  `public_capfun_register`, `private_capfun_register`
- The real init work (e.g. `chip_tm_init` at `.text+0x36ac`, 0x650 bytes
  big) lives in `.text` — the vendor didn't mark these functions
  `__init`, so they're regular `.text` entries

So **"Tier 1 / `--scope init`" means name-pattern matching**, not the
literal `.init.text` section. Suggested default regex:

```python
DEFAULT_INIT_PATTERN = re.compile(
    r"^(init_module|cleanup_module|"
    r"init_.*|.*_init$|"
    r"chip_(tm_init|pp_init|init)|"
    r"sw_init.*|pdt_.*_init|"
    r"(.*_)?probe$)"
)
```

This catches `init_module`, `chip_tm_init`, `sw_init_switch`,
`pdt_ethdriver_init`, etc. — ~10–30 functions per typical stock `.ko`.
Tighter than "every .text function" (which is 235 for switch.ko);
broader than literal `.init.text`.

### Splicer architecture (per-function thunk)

For each matched function:

```
ORIGINAL .text:
    funcN_entry:
        push {regs, lr}       <- gets overwritten
        ...

AFTER SPLICING — .text patched + new .text.splice section added:
    funcN_entry:
        b   thunk_for_funcN   <- 4-byte branch into new section

    .text.splice:
    thunk_for_funcN:
        push {r0-r3, r12, lr}            @ save args + scratch + lr (24 bytes spilled)
        movw r1, #(funcN_entry & 0xffff) @ pass function address as printk arg
        movt r1, #(funcN_entry >> 16)
        adr  r0, fmt_below               @ PC-relative load of fmt string
        bl   printk                      @ NEEDS R_ARM_CALL RELOC
        pop  {r0-r3, r12, lr}            @ restore
        <displaced_instruction>          @ execute what we overwrote
        b    funcN_entry+4               @ resume in the function
    fmt_below:
        .asciz "[STOCK %08x]\n"          @ ONE shared fmt; %x = func entry addr
```

**Why one shared fmt string**: avoids per-function fmt allocation. The
function name is recoverable post-hoc by matching the printed address
against the .ko's symbol table (`nm switch.ko | grep <addr>`).

### Required ELF surgery

1. Add new section header: `.text.splice` (PROGBITS, SHF_ALLOC | SHF_EXECINSTR)
2. Add new section header: `.rel.text.splice` (REL, link → .symtab, info → .text.splice)
3. Find `printk` symbol index in `.symtab` (already UND in switch.ko)
4. For each function spliced:
   - Append the thunk bytecode (60-72 bytes typically) to `.text.splice`
   - Append a relocation entry to `.rel.text.splice`:
     `(offset_of_bl_printk_in_splice, R_ARM_CALL=28, printk_sym_idx)`
5. Patch the original function entry in `.text`: replace first 4 bytes
   with `b thunk` (encoded as `0xea000000 | ((thunk_relative_offset >> 2) - 2) & 0xffffff`)
6. Update the ELF section header table + (if needed) the section string
   table to hold the new section names

### ARM instruction encodings needed (manual hex, no toolchain needed)

| Mnemonic | Hex |
|---|---|
| `push {r0-r3, r12, lr}` (= `stmdb sp!, ...`) | `0xe92d500f` |
| `pop {r0-r3, r12, lr}` (= `ldmia sp!, ...`) | `0xe8bd500f` |
| `movw r1, #imm16` | `0xe3001000 \| (imm & 0xfff) \| ((imm >> 12) << 16)` |
| `movt r1, #imm16` | `0xe3401000 \| (imm & 0xfff) \| ((imm >> 12) << 16)` |
| `adr r0, fmt` (= `add r0, pc, #imm8`) | `0xe28f0000 \| imm8` (max ±255 with rotation) |
| `bl printk` placeholder (reloc fills in) | `0xebfffffe` |
| `b imm24` | `0xea000000 \| ((offset/4 - 2) & 0xffffff)` |
| `nop` | `0xe1a00000` (mov r0, r0) |

### Edge cases to handle (or skip-and-warn)

| Case | Issue | Strategy |
|---|---|---|
| Displaced instruction is PC-relative (`bl`, `b`, `ldr [pc, ...]`) | Executing it from the thunk gives wrong target | Detect via opcode pattern; SKIP that function with a warning |
| Displaced instruction is conditional (e.g., `bne`, `cmpge`) | Same as above + condition flags must be preserved | SKIP with warning (rare at function entry, prologues are always unconditional) |
| Function too small (< 4 bytes) | Can't fit `b thunk` | SKIP with warning |
| `adr r0, fmt` offset overflows (±255 with rotation, or ~2KB with PC+8 quirk) | Can't address fmt inline | Pad thunk so fmt sits within range, OR use `movw/movt` to load address explicitly |
| `printk` symbol not present in `.symtab` | Can't generate relocation | Add as new UND symbol (this is more ELF surgery) |

### Smoke-test target

`build/drivers/net/ethernet/zte/zx279128-eth.ko` (our own mainline driver).

1. Splice `zx_eth_open` with the tool
2. Build a mainline kernel containing the patched module
3. RAM-boot via `python3 lib/uart.py auto_bootm_dtb_appended`
4. `ip link set eth0 up` (triggers `zx_eth_open`)
5. Verify `[STOCK 00XXXXXX]` line appears on UART

### What's verified (Phase 1 prerequisites)

- ✅ `pyelftools` installed
- ✅ `switch.ko` ELF structure understood (235 FUNC symbols, sections mapped)
- ✅ `printk` is already an UND symbol in switch.ko (relocation target available)
- ✅ Cspd-patched stock + kmsg2uart bridge live (Phase 0 done)
- ✅ Stock .ko files accessible via `ext/kmodules_dump/`
- ⏳ ARM thunk encoding designed but NOT yet implemented in code
- ⏳ ELF section surgery designed but NOT yet implemented in code
- ⏳ Smoke test on `zx279128-eth.ko` NOT yet run

## References

- `tasks/99.01.linux-stockport/auto_patch_plat.py` — prior art (the splicing pattern)
- `docs/ITERATE.md` Loop B — the iter cycle this methodology unlocks
- `ROADMAP.md` "Now" step 2 — this is the unblock for step 3 (RX work)
- `LEARNED.md` "How to observe what stock kernel modules do at runtime" —
  high-level summary of why this is the only path
- Related: [[research/rx_path_dead]] (the first customer for this tool)
