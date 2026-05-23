# orca-h3600p — Marcos del Sol Vives' H3600P RE artifacts

**Source**: https://orca.pet/zteh3600p/ — the writeup that bootstrapped
this whole project. Marcos extracted and analyzed firmware from his own
H3600P unit.

**This is a different physical device.** Same model family (H3600P) but
not the unit we own. Use as **reference / cross-check / Ghidra fodder**,
not as source-of-truth for our hardware.

The full 375 MB orca_pet tree is now archived here (was at ZTE/orca_pet/
before consolidation).

## Layout

```
refs/orca-h3600p/
├── README.md                       ← this file
├── Untitled Document               ← orca's notes (links to kanxue, chinadsl, github)
│                                     curated copy lives in docs/EXTERNAL_RESEARCH.md
├── device/                         orca's working dirs (decompiled, firmware, ghidra, rootfs)
├── extracted_files/                orca's harvest of removed-from-mainline ZX support:
│   ├── bindings/                     DT binding YAML/txt for ZX296702 / ZX296718
│   ├── clk/                          clock drivers from old mainline
│   ├── dma/, dts/, gpio/, headers/, mach-zx/, pinctrl/, soc/
│   ├── decompiled/                   orca's Ghidra-decompiled snippets
│   └── zx_defconfig                  the old mainline ZX kernel defconfig
├── firmware/                       orca's NAND extracts (his unit):
│   ├── bootloader.bin (+.xz)
│   ├── kernel.bin
│   ├── rootfs.bin
│   ├── firmware.bin (+.xz)
│   ├── blob_360000.bin
│   ├── vmlinux.bin                   (orca's vmlinux — different md5 from our ext/extracted/vmlinux.bin)
│   ├── extracted.dts ★               H3600 DTS — IDENTICAL md5 to what was in our ext/ before this cleanup
│   └── extracted.dtb ★               compiled DTB — same
├── ghidra/                         logs from orca's Ghidra headless runs
└── kernel_elf/
    └── kernel.elf (+.xz)             ★ unstripped ARM ELF — symbol gold for Ghidra
```

★ The starred items are the highest-value reuses.

## Key reuses

### `kernel_elf/kernel.elf` — symbols for Ghidra

Open in Ghidra to get function names (`chip_tm_init`, `pon_tm_net_int`,
etc.) that **our** `ext/extracted/vmlinux.bin` (raw `data`, no symbol
table) doesn't expose. Then look up the corresponding address and check
whether our vmlinux has the same bytes:

```sh
cmp -n 64 -i $((0x12a4)):$((0x12a4)) \
    refs/orca-h3600p/kernel_elf/kernel.elf \
    ext/extracted/vmlinux.bin
# If identical → orca's symbol is at the same address on our unit.
# If different → derive the offset, or RE on our unit directly.
```

### `firmware/extracted.dts` + `extracted.dtb` — H3600 device tree

Used to live in our `ext/extracted/h3600_real.dts` until the 2026-05-23
reorg recognized they were orca-sourced (identical md5 to orca's). They
describe the same hardware model so the content is fine, but the proper
home is `refs/` since the bits came from orca's extraction, not from
ours.

If we ever need a DTS guaranteed to be from our own unit, we'd extract
fresh from `/proc/device-tree` on the running stock kernel and write to
`ext/our_extracted_dts.dts`. Until then, treat this one as "good
enough, verified-matches-orca".

### `extracted_files/` — orca's mainline-archaeology raw material

orca harvested the source files for removed-from-mainline ZX support
(clocks, GPIO, DMA, pinctrl, mach-zx, DT bindings) at the time of his
analysis. **Our equivalent + analysis is in
[`tasks/00.10.04.mainline-archaeology/`](../../tasks/00.10.04.mainline-archaeology/)**
(the Spanish report `KERNEL_ARCHAEOLOGY_ES.md`).

Orca's snapshot is useful as a "what existed when" reference; the
archaeology report is more current.

## What LIKELY matches between orca's H3600 and ours

- Function names, struct layouts, EXPORT_SYMBOL lists in the kernel
- Most register offsets
- Most string constants
- TM/switch/PP register layouts

## What LIKELY differs

- AES rootfs key (we have OUR key in `aes_key_discovered` memory; orca's
  writeup describes the derivation, may or may not match per-unit)
- MAC addresses, calibration data, build timestamps
- Per-unit defcfg/usercfg partition content
- Some `/proc/cpuinfo`-like dynamic strings

## When NOT to use

If you're about to **flash, patch, or modify** a binary that will run on
**our** device → always rebuild or extract from `ext/`. Orca's binaries
are read-only references.

## See also

- `docs/EXTERNAL_RESEARCH.md` — orca writeup + kanxue/chinadsl thread links
- `tasks/00.10.04.mainline-archaeology/KERNEL_ARCHAEOLOGY_ES.md` — successor to orca's `extracted_files/` work
- Memory `aes_key_discovered` — our unit's AES key (derived per orca's method but for OUR device)
- Memory `gpl_legitimacy_context` — why all this RE work is legitimate
