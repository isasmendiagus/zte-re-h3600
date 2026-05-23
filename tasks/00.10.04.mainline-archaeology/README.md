# mainline-archaeology — what's reusable from old mainline ZX support

**ID**: 00.10.04
**Parent**: [00.10 explore](../00.10.explore/)
**Children**: none
**TaskList items**: none directly
**Consumed by**: [00.openwrt-port](../00.openwrt-port/) — the primary customer (deciding what to resurrect for OpenWrt)
**Status**: ✅ DONE — archaeology report complete. Append updates only if mainline ZX support changes.

## What this is (English summary of the Spanish report)

A research report cataloging the **ZTE ZX platform support that existed
in mainline Linux from April 2015 to January 2021**, and how much of it
is reusable for our ZX279128S port.

In short:

- ZTE ZX support lived in mainline between commits `acede515b3a5` (Apr 2015,
  Jun Nie / Linaro) and `89d4f98ae90d` (Jan 2021, Arnd Bergmann's sweep that
  removed it all)
- Two SoCs were covered: **ZX296702** (Cortex-A9 dual, set-top-box — closest
  to our ZX279128S) and **ZX296718** (Cortex-A53 quad, set-top-box)
- Removal was driven by lack of upstream maintainers, not by technical issues

## Reusable bits for our OpenWrt port

(per the full report)

| Subsystem | Old mainline driver | Reusable for ZX279128S? |
|---|---|---|
| Clocks (TOP / LSP0 / LSP1) | `drivers/clk/zte/clk-zx296702.c` | ✅ same PLLs + register model |
| GPIO | `drivers/gpio/gpio-zx.c` | ✅ register layout matches |
| DMA controller | `drivers/dma/zx_dma.c` | ✅ compatible `"zte,zx296702-dma"` |
| SMP (boot CPU1) | `arch/arm/mach-zx/platsmp.c` | ✅ same Cortex-A9 pattern |
| Power domains (PCU) | `arch/arm/mach-zx/zx296702-pm-domain.c` | ⚠️ probably, depends on bitmasks |
| MMC (DesignWare) | `drivers/mmc/host/dw_mmc-zx.c` | ⚠️ only if H3600 uses DW-MSHC |
| UART PL011 | mainline `amba-pl011.c` | ✅ already covered (with our ZTE-shifted-DR patch) |
| Switch + GE PHY + RGMII | — | ❌ NO mainline support; have to write it (this is what `00.01.eth-driver` does) |
| NAND Denali | generic `denali_dt.c` | ⚠️ DT wiring needed |
| USB 3.0 (DWC3) | generic `dwc3-of-simple.c` | ⚠️ clock/reset glue needed |
| PCIe 2.0 | — | ❌ no traces in mainline ZX support |
| xPON SerDes | — | ❌ doesn't matter (external ONT) |

## What this directly informs

When `00.openwrt-port` becomes active, the resurrection plan is:

1. Take a modern LTS upstream (fetch upstream torvalds/linux per `docs/KERNELS.md` "kernel #4" recipes; or fold into our active `zxic/linux-v6.6/` as `upstream` remote)
2. **Cherry-pick the ZX296702 commits that produced the green-checkmark
   drivers above** (the chronological list is in the full report)
3. Apply our ZX279128S-specific patches (in `tasks/00.openwrt-port/kernel-patches/`)
4. Use our `zx279128-eth.c` for the network driver
5. Wrap as OpenWrt `target/linux/zxic/`

## Files

- **`KERNEL_ARCHAEOLOGY_ES.md`** — the full report, **in Spanish**
  (~630 lines). Contains the commit-by-commit timeline, the file
  inventory, the device-tree comparison table, and a driver-by-driver
  analysis. Read this when you actually start the OpenWrt port work.

## Why this is a task (not just a doc in `docs/`)

It's the **deliverable of completed exploration work** — same kind of
output that `00.10.01.re-vmlinux` will produce as `findings/` accumulate.
Co-locating with sibling explore tasks makes its provenance clear.

## See also

- `tasks/00.openwrt-port/` — the primary consumer; will branch from this
- `tasks/00.openwrt-port/kernel-patches/` — our ZX279128S patches that
  layer on top of the resurrected ZX296702 support
- `refs/stefan-zx297520/` — Stefan's port for the sibling ZX297520v3
  SoC; complementary archaeology
- `docs/KERNELS.md` "kernel #4 — Upstream master" — operational view
