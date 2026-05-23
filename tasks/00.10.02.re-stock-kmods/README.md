# re-stock-kmods — knowledge base for the stock H3600 kernel modules

**ID**: 00.10.02
**Parent**: [00.10 explore](../00.10.explore/)
**Children**: none
**TaskList items**: none directly (consumers own their tasks)
**Consumed by**: [00.01 eth-driver](../00.01.eth-driver/) (heaviest user — TM/switch/PP/CLA/IDM RE), [00.02 stock-shell](../00.02.stock-shell/) (cspd-adjacent modules), and any future task touching stock-kernel modules
**Status**: 🧠 KNOWLEDGE BASE — append-only. Read `../00.10.explore/README.md` for rules of engagement.

## What's here

This task owns the Ghidra analysis of all stock `.ko` files that ship in
the H3600's slot-A rootfs. A **single Ghidra project** holds all of them
imported as separate binaries — that's what gives us cross-binary call
graphs (e.g. "this exported symbol from `tm.ko` is called from `switch.ko`").

```
./ghidra/h3600_kmods.gpr        ← open in Ghidra
./ghidra/h3600_kmods.rep/       ← project data (multiple .ko's analyzed; ~16 binaries)
./findings/                     ← markdown notes promoted from consumer tasks
```

## What's analyzed (per the project's idata/ contents)

Per the `idata/00/0000000N.db/` enumeration in the project, there are
~16 separately analyzed binaries. The big ones from `ext/rootfs/kmodule/`:

- `plat-zxylzb_9128S.ko` — platform glue
- `switch.ko` — switch + TM operations
- `tm.ko` — Traffic Manager
- `idmfdb.ko` — IDM CPU port (descriptor rings)
- `pp.ko` — Packet Processor
- `cla.ko` — Classifier
- `bmu.ko` — Buffer Manager
- (plus others — open the project to enumerate)

## Why one project for all of them

Stock `.ko`s call each other via `EXPORT_SYMBOL`. With all of them in
the same Ghidra project, clicking a function jumps to its definition
even when it's in a different `.ko`. Splitting per-module would lose
this — and the calls are exactly what we need to RE the init sequences
(e.g. `chip_tm_init` in `switch.ko` calls into `tm.ko`).

## Tooling

The shared dump scripts at `zxic/ghidra/dump_*.py` (the older RE
tooling) operate on **this** project for the kmod-related dumps:

- `dump_ko.py`, `decompile_ko.log`, `run_decompile_ko.sh` — Ghidra
  headless scripts that batch-decompile functions to text

The `run_decompile_ko.sh` hardcodes this project's path; if you ever
re-locate the project you must update that script.

## Rules of engagement

See [`../00.10.explore/README.md`](../00.10.explore/) "Rules of engagement"
section. TL;DR: **append-only labels/comments; no destructive renames.
Fork to your consumer task's local `ghidra/` for experiments.**

## Currently known findings

(populated as discoveries from consumer tasks get promoted here. Today
this is empty — existing kmod findings still live in consumer tasks'
`research/` notes, e.g. `00.01.eth-driver/research/rx_path_dead.md`.)

## See also

- `docs/KERNELS.md` "Stock kernel — The .ko files you'll be patching" — what each .ko does
- Sibling: [00.10.01 re-vmlinux](../00.10.01.re-vmlinux/) for the kernel proper
- `ghidra/README.md` (top-level) — shared dump tooling
