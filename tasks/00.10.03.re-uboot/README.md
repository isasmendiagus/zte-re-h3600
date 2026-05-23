# re-uboot — knowledge base for the H3600 U-Boot bootloader

**ID**: 00.10.03
**Parent**: [00.10 explore](../00.10.explore/)
**Children**: none
**TaskList items**: none directly
**Consumed by**: [00.03 nand-flash](../00.03.nand-flash/) (BootPara structure, csp_crc impl, nand command details), [00.openwrt-port](../00.openwrt-port/) (boot flow for OpenWrt image format)
**Status**: 🧠 KNOWLEDGE BASE — append-only. Read `../00.10.explore/README.md` for rules of engagement.

## What's here

The Ghidra analysis of the H3600's U-Boot binary. U-Boot is what we
drive over UART for every `tftp + bootm` and every `nand erase + nand write`,
so understanding what it actually does (especially the cspstart slot
selection + CRC checks) is high-leverage.

```
./ghidra/h3600_uboot.gpr
./ghidra/h3600_uboot.rep/
./findings/
```

## What the binary is

- Extracted from NAND partition `0x000000..0x0c0000` (the bootloader region)
- ZTE custom U-Boot — based on mainline but with vendor patches
- See `docs/NAND_LAYOUT_AND_BOOT.md` for the boot-flow narrative

## High-value RE targets in this binary

- `csp_crc` — the CRC function used to validate BootPara headers (turns out it's just `zlib.crc32` per `tools/find_csp_crc.py`)
- `cspstart` — slot selection logic (which slot's kernel/rootfs gets loaded)
- `bootm` arg parsing — confirms only-1-arg behavior (forces appended DTB)
- `nand` command implementations (erase, write, read)
- TFTP transfer code (for diagnosing why slow / why hangs)

## Rules of engagement

See [`../00.10.explore/README.md`](../00.10.explore/). U-Boot has a lot
of standard mainline-U-Boot code; **don't rename mainline U-Boot functions
to ZTE-flavored names** — keep the upstream names so cross-reference with
public U-Boot source stays trivial. Annotate ZTE-specific patches with
labels like `[ZTE]` to flag them.

## Currently known findings

(empty for now; existing findings live in `docs/ARCHITECTURE.md`, `docs/NAND_LAYOUT_AND_BOOT.md`, and `tasks/00.03.nand-flash/README.md` — promote them here as appropriate)

## See also

- `docs/ARCHITECTURE.md` "csp_crc" — what we already know
- `tasks/00.03.nand-flash/README.md` — operational consumer of this analysis
- `tools/find_csp_crc.py` — verified our CRC understanding against U-Boot's impl
- Sibling: [00.10.01 re-vmlinux](../00.10.01.re-vmlinux/), [00.10.02 re-stock-kmods](../00.10.02.re-stock-kmods/)
