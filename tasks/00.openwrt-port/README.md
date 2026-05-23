# openwrt-port — port to OpenWrt (the actual end-goal)

**ID**: 00 (root)
**Parent**: — (this IS the root goal)
**Children**: [00.01 eth-driver](../00.01.eth-driver/), [00.02 stock-shell](../00.02.stock-shell/), [00.03 nand-flash](../00.03.nand-flash/), [00.05 firmware-load](../00.05.firmware-load/), [00.06 platform-drivers](../00.06.platform-drivers/) (umbrella; 1 active child), [00.10 explore](../00.10.explore/) (umbrella with 4 RE knowledge-base tasks)
**TaskList items**: none directly — every child task contributes
**Status**: 📋 PLANNED — preparatory archaeology done, no active work yet.
This is **stage 5/6** of `ROADMAP.md`. Don't start until eth-driver
carries traffic (stage 3 done).

## Goal

Run OpenWrt on the H3600, replacing the stock 4.1.25 kernel + ZTE
proprietary userspace with a clean upstream Linux + OpenWrt rootfs.

## Approach: mainline ZX resurrection

The ZTE ZX platform was removed from mainline Linux in **January 2021**
(commit `89d4f98ae90d`, Arnd Bergmann's `ARM: remove zte zx platform`).
Before that, mainline had usable support for the sibling SoC ZX296702
(Cortex-A9, same family as our ZX279128S).

The plan is:
1. Take a modern LTS kernel (or current upstream — see `docs/KERNELS.md` "kernel #4" for re-fetch recipes).
2. Cherry-pick the commits that introduced ZX296702 support before they
   were removed.
3. Add **our** patches (in `kernel-patches/`) to adapt that support for
   the ZX279128S specifically.
4. Use our `zx279128-eth.c` from `tasks/00.01.eth-driver/` as the network driver.
5. Wrap as OpenWrt `target/linux/zxic/`.
6. Package as cspstart-compatible slot A image so it boots from NAND.

The full archaeology — what was removed, what's reusable, what isn't —
lives in its own task: **[00.10.04 mainline-archaeology](../00.10.04.mainline-archaeology/)**.
Read its README + the full `KERNEL_ARCHAEOLOGY_ES.md` (Spanish) before
doing any real work here.

## Layout

```
tasks/00.openwrt-port/
├── README.md                    ← you are here
│   (archaeology moved → tasks/00.10.04.mainline-archaeology/)
├── kernel-patches/              ← OUR patches for the resurrected mainline (apply on top of upstream)
│   ├── clk/clk-zx279128s.c        clock tree for our SoC
│   ├── configs/zx279128s_defconfig kernel config
│   ├── dts/zx279128s.dtsi         SoC-level device tree
│   ├── dts/zx279128s-h3600.dts    board-level device tree
│   └── mach-zx/zx279128s.c        machine descriptor
└── scripts/
    ├── setup_fork.sh             clone upstream + cherry-pick ZX resurrection commits
    └── build_kernel.sh           wrap make/mkimage with the right flags
```

⚠️ The `scripts/` were written before the H3600→zxic rename — paths
inside them point at `/srv/tftp` and the old `linux-zxic-fork` location.
**Treat as design reference, not as runnable.** Reuse the strategy, not
the literal commands.

## Why this is parked

The eth-driver work (stages 2-3) has to be solved first. Without a
working driver, an OpenWrt build is just a brick with a fancy bootlog.
Once `tasks/00.01.eth-driver/` reports sustained ping → start here.

## See also

- `docs/KERNELS.md` — describes all 3 kernel trees + the upstream master
  (upstream torvalds/linux; fetch on demand per `docs/KERNELS.md` "kernel #4") that this work will branch from
- `ROADMAP.md` stage 5/6 — the milestones this task fulfills
- `../../refs/stefan-zx297520/` — Stefan's port for the sibling
  ZX297520v3 SoC. Same family, same archaeology pattern. Read his
  README before starting — it's the closest thing to a blueprint.
- Memory `gpl_legitimacy_context` — why this work is fine to publish
- `KERNEL_ARCHAEOLOGY_ES.md` §7 "Plan de acción concreto" — concrete
  step-by-step plan from the archaeology report
