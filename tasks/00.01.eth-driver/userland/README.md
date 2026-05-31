# Soft-float userland for the no-VFP ZX279128S (initramfs)

## Problem
The Cortex-A9 in this SoC has **no VFP** (Features: no vfp/neon). The previous
initramfs busybox was compiled with `Tag_FP_arch: VFPv2` (hardfloat) → any applet
that touches float (ping RTT stats, ip, brctl, ls formatting) executes an illegal
VFP instruction → **SIGILL (exit=4)**. Only `sh`/`cat`/`grep` survived.

## Fix (2026-05-31)
Rebuilt busybox **soft-float** so it emits zero VFP instructions:
- Toolchain: Bootlin **armv5-eabi--glibc--stable-2018.11-1** (soft-float, no VFP;
  armv5 code runs fine on the A9). Download:
  https://toolchains.bootlin.com/downloads/releases/toolchains/armv5-eabi/tarballs/armv5-eabi--glibc--stable-2018.11-1.tar.bz2
- busybox 1.31.0, `make defconfig` + `CONFIG_STATIC=y`.
- Build: `PATH=<tc>/bin:$PATH make CROSS_COMPILE=arm-linux- -j8`
- Result ABI: `Tag_CPU_arch: v5TEJ`, NO `Tag_FP_arch` → soft-float. (`busybox.softfloat`)

## Install
Copy to `/tmp/initramfs_extract/bin/busybox` (CONFIG_INITRAMFS_SOURCE points there),
ensure applet symlinks exist (ping ip brctl ifconfig arping udhcpc telnetd route
netstat nc vconfig → busybox), then `build_slotA.py` re-embeds it in the zImage.

## Verified on HW (2026-05-31)
`ip -o addr`, `ip -o link` (shows lan0..3@sw), `ping -c2 127.0.0.1` (2/2 0% loss),
`brctl show` → all exit=0, no SIGILL.
