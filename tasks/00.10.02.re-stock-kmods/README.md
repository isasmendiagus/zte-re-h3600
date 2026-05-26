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

### External tools surveyed (not yet adopted)

Discovered 2026-05-26 during stockport revival prior-art research
(see `../99.01.linux-stockport/findings/external_tooling_prior_art_2026_05_26.md`):

- **FirmSolo** (USENIX Security 2023, github.com/BUseclab/FirmSolo) —
  scans `.ko`s for ksymtab/versions/vermagic, runs Kernel Config
  Reverse Engineering to infer a `.config` whose built `vmlinux`
  exports a superset of every symbol the binary modules need.
  Covers ARM 32-bit Cortex-A9. Highest-EV automation we've found.
- **abidiff / libabigail** (sourceware.org/libabigail) — diffs the
  KMI surface of a stock `.ko` against a self-built `vmlinux`. One
  command lists every struct/function divergence — directly replaces
  the hand-rolled `netdev_probe.ko` struct-offset prober.

## Rules of engagement

See [`../00.10.explore/README.md`](../00.10.explore/) "Rules of engagement"
section. TL;DR: **append-only labels/comments; no destructive renames.
Fork to your consumer task's local `ghidra/` for experiments.**

## Currently known findings

### Index
- [`findings/HW_BLOCKS_INVENTORY.md`](findings/HW_BLOCKS_INVENTORY.md) —
  **canonical HW inventory** of every block discovered in the stock kmods.
  13 sub-blocks (sbrg, spa, cla, dpa, adm, sadm, sdet, greg, qmg, red,
  pm, uopc/sopc, smct, usch, sch) + the 9 MMIO regions stock ioremaps
  (vs our 1) + the 5 IRQs stock services (vs our 1).
- [`findings/lan_up_port_lifecycle.md`](findings/lan_up_port_lifecycle.md) —
  how stock derives the TX desc port encoding (`lan_up_port` global, set
  by `tm_set_p2pmode` from `sw_other_set_wan_lan_switch`).
- [`findings/tx_path_stock_decomp.md`](findings/tx_path_stock_decomp.md) —
  TX desc bit-level format from `pon_tm_data_raw_send` decomp. Documents
  the descriptor we now emit (desc[11]=0x21, desc[0]=0xc9, pad-to-0x40).

### Massive pseudo-C corpus

All function bodies from the stock .ko files, decompiled headless and
saved as text — grep-able without needing to re-open Ghidra:

- [`findings/decomp_all_plat_zxylzb_9128S.c`](findings/decomp_all_plat_zxylzb_9128S.c) — 334 fns, 273 KB
- [`findings/decomp_all_switch.c`](findings/decomp_all_switch.c) — 423 fns, 412 KB
- [`findings/decomp_all_tm.c`](findings/decomp_all_tm.c) — 1330 fns, 1.9 MB
- [`findings/decomp_all_idmfdb.c`](findings/decomp_all_idmfdb.c) — 82 fns, 65 KB
- [`findings/decomp_all_zx_ponreg.c`](findings/decomp_all_zx_ponreg.c) — 10 fns, 4 KB
- Targeted decomps (older, narrower):
  `decomp_pon_tm_2026-05-24.txt`, `decomp_pon_tm_net_tx_2026-05-24.txt`

**Regenerate**: see the Jython script pattern in `findings/decomp_all_*.c`
header comment, or rerun via `analyzeHeadless ghidra/ h3600_kmods
-process <ko> -noanalysis -scriptPath /tmp -postScript decomp_all.py`.

## See also

- `docs/KERNELS.md` "Stock kernel — The .ko files you'll be patching" — what each .ko does
- Sibling: [00.10.01 re-vmlinux](../00.10.01.re-vmlinux/) for the kernel proper
- `ghidra/README.md` (top-level) — shared dump tooling
