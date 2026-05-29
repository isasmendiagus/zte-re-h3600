# splice_poc — proof-of-concept ladder for binary-splicing approaches

**Status**: closed — findings captured in this README; future PoCs go in
sibling files here.

## Why this exists

When we got blocked trying to build the printk-injection splicer
(`tasks/00.01.eth-driver/scripts/ko_printk_splice.py`), I asserted "LIEF
0.17.6 is buggy on kernel modules" — without verification. User pushed back
and suggested a small PoC ladder instead of speculation.

This subdir holds the PoCs we ran (or might run) to establish facts before
committing to a tooling direction.

## PoC results (2026-05-23)

| PoC | Question | Result |
|-----|----------|--------|
| 0 — roundtrip | Does `lief.parse(.ko); binary.write(...)` produce a valid ELF? | ✅ **Works**. 202,792 → 202,792 bytes, valid ELF header, 235 FUNC syms preserved exactly, 40 sections preserved. Bytes differ (LIEF reorganizes internally) but structurally identical. |
| 1 — symbol/section preservation after roundtrip | Are the 1748 symbols + 235 FUNC syms + 40 sections all still there? | ✅ identical sets |
| 2 — add new section, write | Does `binary.add(Section(...), loaded=True/False)` actually add a section? | ❌ **NO** with either flag value:<br>• `loaded=False` → crash (`IndexError: unordered_map::at`, "Node not found")<br>• `loaded=True` → silently drops the section (write succeeds, output still has 40 sections — same as input — but no `.text.splice`); `add()` returns `None` |
| 3 — add section + relocations | n/a | Blocked by PoC 2 failure |
| 4 — full splicer end-to-end | n/a | Blocked by PoC 2 failure |

## Implications

LIEF can READ and ROUND-TRIP ARM REL `.ko` files cleanly, but it **cannot
add new sections to them** in version 0.17.6.

This was confirmed via 4 PoCs locally AND by searching the LIEF project:

- **GitHub issue [lief-project/LIEF#661](https://github.com/lief-project/LIEF/issues/661)** —
  *"add section in ELF file : unexpected section size"* — open since 2022,
  labeled `help wanted`. Multiple users (most recent: 2025-03) report the
  same broken behavior. No fix landed.
- The LIEF maintainer (Romain Thomas) explains in the thread that the
  +4K alignment / segment-creation logic interacts badly with files that
  don't have proper LOAD segments. That's exactly our case (REL = no LOAD
  segments).
- LIEF blog post referenced by the maintainer for context:
  [Challenges in Modifying ELF Binaries (2022-01-23)](https://lief-project.github.io/blog/2022-01-23-new-elf-builder/).
  Doesn't document a workaround for REL files.

LIEF 1.0.0 docs exist but I have 0.17.6 installed; the open issue applies
to current LIEF as well per the 2025 commenter. If we ever want to revisit
binary-patching later, the first thing to try is whether 1.0.0 stable
contains a fix (unlikely given the issue is still open).

## What LIEF *could* still do for us, if we wanted

- Use `binary.patch_address(addr, bytes)` to modify EXISTING bytes
- Use this to repurpose existing `printk` call sites in `init_module`
  (which already exist in switch.ko per the disassembly)
- Modify the existing fmt strings in `.rodata` to print custom messages

That's a viable but very limited form of instrumentation — only as many
trace points as `init_module` already has `printk` calls (~2 per module).
Not enough for tracing `chip_tm_init`'s call chain.

## Conclusion + path forward

Binary-patching approach is **not viable with LIEF 0.17.6** for our use
case (need to splice ~7+ functions, requires new section + new relocations).

**Pivot remains**: write a runtime tracer kernel module (`tracer.ko`)
in C, source-controlled, that uses `kallsyms_lookup_name()` to hook stock
symbols at insmod time. Full design in
`tasks/00.01.eth-driver/PLAN_init_debug.md` "Phase 1 pivot" section.

## Future PoCs (run only if the runtime-tracer approach hits a wall)

| PoC | Question |
|-----|----------|
| 5 | Does LIEF 1.0.0 (when stable / available) handle section addition for REL files? |
| 6 | Can we use `patch_address` to repurpose existing `printk` calls for trace points? |
| 7 | Are there ARM-specific binary patchers (radare2 r2pipe, etc.) that handle `.ko` section addition correctly? |
