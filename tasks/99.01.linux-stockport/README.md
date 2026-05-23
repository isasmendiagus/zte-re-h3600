# linux-stockport — vanilla 4.1.25 rebuild with KGDB/KPROBES (PARKED)

**ID**: 99.01
**Parent**: 99 (parked-work category; no parent README — 99 is a category prefix)
**Children**: none
**TaskList items**: #94 (completed)
**Status**: ⛔ PARKED

## What this was

Vanilla `linux-4.1.25.tar.xz` + ZTE board-file port + 4 EXPORT_SYMBOL
patches + KGDB/KPROBES/FTRACE enabled. Goal was to load the factory
stock `.ko` files on this kernel so we could use debug tooling (kprobes,
ftrace, KGDB) that the factory 4.1.25 kernel was built without.

## Why parked

Full source-level recreation of ZTE's downstream patches proved too
brittle. We pivoted to the **printk-injection methodology** which gives
observability without rebuilding the kernel — see
`../00.01.eth-driver/research/printk_injection_methodology.md`.

## What's still useful here

The `build.sh` header documents the **critical knobs** for any future
4.1.25 build on this hardware:

- Toolchain: hard-float Buildroot GCC 7.3 at
  `~/toolchains/armv7-eabihf--glibc--stable-2018.11-1`
- `LOADADDR=0x40008000` (NOT mainline's `0x42000000`)
- `PHYS_OFFSET=0x40000000`
- `CONFIG_ARCH_ZX=y` (re-pin every olddefconfig)
- `CONFIG_UNINLINE_SPIN_UNLOCK=y` (else stock `.ko` can't resolve `_raw_spin_unlock`)
- 4 EXPORT_SYMBOL patches: `kallsyms_lookup`, `find_task_by_vpid`,
  `show_stack`, `_raw_spin_unlock`

Full context in `docs/KERNELS.md` "kernel #3 — Stockport (parked)".

## Don't resurrect without strong reason

If you find yourself reaching for this folder, first ask: "can I solve
this with a printk-splice instead?" 99% of the time the answer is yes,
and it's a 30-second iter loop vs. a multi-day kernel-rebuild rabbit hole.
