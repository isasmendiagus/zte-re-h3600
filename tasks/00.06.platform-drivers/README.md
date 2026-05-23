# platform-drivers — resurrect the removed-from-mainline ZX SoC drivers

**ID**: 00.06
**Parent**: [00 openwrt-port](../00.openwrt-port/)
**Children**: [00.06.01 clk-driver](../00.06.01.clk-driver/) (active), 00.06.02..06 (planned placeholders below)
**TaskList items**: none directly (per-child)
**Status**: 🚧 PLANNED — first child (clk-driver) just stood up; rest follow as needed

## What this umbrella is for

When ZTE's ZX platform code was removed from mainline in **January 2021**
(commit `89d4f98ae90d`, "ARM: remove zte zx platform"), we lost the
**foundational platform drivers** that any kernel on this SoC needs.

Our current `zxic/linux-v6.6/` has only a **minimal stub** (`mach-zx/zx279128s.c`,
38 lines — just enough to map the UART and boot). Everything else we get
away without by **brute-replaying stock register dumps in our eth driver**.
That hack doesn't scale to a second driver.

This umbrella holds the tasks that **bring back each removed driver as a
proper Linux driver** — adapted from the ZX296702 originals (which our
ZX279128S is register-compatible with, per the archaeology report).

## The cherry-pick catalog

Cross-reference with [`tasks/00.10.04.mainline-archaeology/`](../00.10.04.mainline-archaeology/)
"reusable bits" section. Each entry below is a future or active task.

| Task | Brings back | Priority | Why |
|------|-------------|---------|-----|
| [00.06.01 clk-driver](../00.06.01.clk-driver/) | `drivers/clk/zte/clk-zx296702.c` | 🔴 **CRITICAL** | Without this, no standard driver can `clk_get()` → most drivers fail. Today we brute-replay regs in our eth driver to work around. Doesn't scale. |
| 00.06.02 gpio-driver (placeholder) | `drivers/gpio/gpio-zx.c` | 🟡 medium | Router LEDs, WPS buttons, factory-reset, GPIO-controlled PHY reset. We get away without it today but OpenWrt needs it. |
| 00.06.03 dma-driver (placeholder) | `drivers/dma/zx_dma.c` | 🟡 medium | USB / MMC / SPI fall back to PIO mode without it (slow). |
| 00.06.04 platsmp (placeholder) | `arch/arm/mach-zx/platsmp.c` | 🟢 low | Single-core boot works; SMP is just lost CPU. |
| 00.06.05 pm-domains (placeholder) | `arch/arm/mach-zx/zx296702-pm-domain.c` | 🟢 low | Power-gating idle blocks (idle-power optimization). |
| 00.06.06 dt-bindings (placeholder) | `Documentation/devicetree/bindings/.../zte*.yaml` + `arch/arm/boot/dts/zte/zx296702.dtsi` | 🟡 medium | Bindings + reusable DTSI base. Without these, every DTS is hand-written. |

## Source for the cherry-picks

The exact commit hashes are in [`tasks/00.10.04.mainline-archaeology/KERNEL_ARCHAEOLOGY_ES.md`](../00.10.04.mainline-archaeology/KERNEL_ARCHAEOLOGY_ES.md)
("Línea temporal del soporte ZX en mainline"). High-level:

- Jun Nie / Linaro authored most of them between 2015-2017
- Removal sweep: Arnd Bergmann, 2021-01-20 (`89d4f98ae90d` + ~11 follow-ups)
- Source: clone any kernel version BEFORE 5.11 (e.g. `git checkout v5.10`)
  and the files are there

## How tasks here relate to other artifacts

```
tasks/00.10.04.mainline-archaeology/    ← analysis: WHAT exists, WHY useful
                ↓
tasks/00.06.platform-drivers/           ← this umbrella: WHEN/WHO ports each
                ↓
tasks/00.06.01.clk-driver/              ← actual porting work for one driver
                ↓ (output)
zxic/linux-v6.6/drivers/clk/zte/        ← the resurrected files land here
tasks/00.openwrt-port/kernel-patches/clk/clk-zx279128s.c  ← ZX279128S adaptation on top
                ↓
zxic/build/                             ← compiled into the kernel
```

## When NOT to spawn a new platform-driver task

- If the driver works "well enough" via our brute-replay hack and we have
  no second consumer that needs it — defer
- If we're months away from openwrt-port → focus on RX/TX driver work first
- If the original ZX296702 driver was for a feature this SoC doesn't have
  (e.g. specific peripherals that ZX279128S omits)

## Activation gate

Most tasks here are placeholders until openwrt-port becomes active work
(stage 5/6 of `ROADMAP.md`). The exception is **00.06.01 clk-driver** —
it's needed sooner than the others because the brute-replay hack we use
today will become painful to extend as we add features.

## See also

- `tasks/00.10.04.mainline-archaeology/` — the analysis driving this work
- `tasks/00.openwrt-port/kernel-patches/` — our ZX279128S-specific patches that layer on top of the resurrected ZX296702 base
- `tasks/00.openwrt-port/scripts/setup_fork.sh` — historical script that did the resurrection in one go (currently STALE, see header)
- `docs/KERNELS.md` — kernel tree map
