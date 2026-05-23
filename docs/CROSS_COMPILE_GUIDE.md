# Cross-compiling binaries for the ZTE H3600 (ZX279128S)

How to build ARM binaries that actually RUN on this box without crashing.

## TL;DR

**Use the SOFT-FLOAT toolchain:** `arm-linux-gnueabi-gcc` (no `-hf`).

```bash
arm-linux-gnueabi-gcc -static -O2 -s -o my_program my_program.c
```

**Verify**: `arm-linux-gnueabi-readelf -A my_program` must show
**no `Tag_FP_arch`** and **no `Tag_ABI_VFP_args`** lines.

If you see `Tag_ABI_VFP_args: VFP registers` → wrong toolchain, the binary
will SIGILL on the device (especially as PID 1).

## Why

The hardware is ARM Cortex-A9 ARMv7. Cortex-A9 in this SoC has **no VFP
unit configured/enabled**. Any binary built for hard-float ABI will issue
VFP instructions at startup → kernel sends `SIGILL` → process dies.

This is non-obvious because:
- The CPU *advertises* itself as Cortex-A9 (which usually has VFP)
- `Tag_CPU_arch: v7`, `Tag_THUMB_ISA_use: Thumb-2` are fine
- The hard-float ABI sneaks in via Ubuntu's default `arm-linux-gnueabihf`
  toolchain — debian/Ubuntu picks that as the default
- The crash often manifests **only as PID 1 init** (child processes
  may not hit a VFP instruction in their lifetime; PID-1 init does)

**Symptom we hit (2026-05-22):** every shell attempt as PID 1 died with
`Comm: sh / init / busybox  exitcode=0x4` (= signal 4 = SIGILL). Took
many hours to diagnose because the SAME busybox binary ran fine as a
child of a soft-float C init.

## Toolchain installation

```bash
# Ubuntu 24.04 (we tested):
sudo apt install gcc-arm-linux-gnueabi binutils-arm-linux-gnueabi

# Verify it's soft-float:
arm-linux-gnueabi-gcc -dumpmachine
# Expected: arm-linux-gnueabi   (NOT arm-linux-gnueabihf)
```

**Do NOT install `gcc-arm-linux-gnueabihf`** unless you have a separate use case.
If both are installed, **always use `arm-linux-gnueabi-` explicitly**.

## Build flavors

### 1. Static C binary (recommended for /init, tools)

```bash
arm-linux-gnueabi-gcc -static -O2 -s -o out/my_prog my_prog.c
# -s = strip
# -O2 = optimize
# -static = self-contained, no .so dependencies
```

Result: ~450 KB binary (because glibc is statically linked). Runs as
PID 1 OK because no VFP.

### 2. Tiny static binary via raw syscalls (advanced)

When 450 KB is too much (e.g., must fit in 22 MB JFFS2 budget):

```bash
arm-linux-gnueabi-gcc -nostdlib -static -O2 -s -o out/tool tool.S
```

See `tasks/00.02.stock-shell/kmsg2uart_nolibc.S` for a working 1.3 KB example
that does mmap + read + write via raw `swi #0` ARM EABI syscalls.

### 3. Dynamic linked against device's uClibc (for stock kernel use only)

Stock device has `/lib/ld-uClibc-0.9.33.2.so` + `/lib/libuClibc-0.9.33.2.so`.
A glibc-built dynamic binary won't load (different dynamic linker name).
Either:
- Cross-build against uClibc (need uClibc toolchain — not worth the effort)
- Use option (1) or (2) above

We tried option (3) once and the device said `not found` because
`/lib/ld-linux.so.3` (glibc loader) wasn't present.

### 4. Cross-compile busybox (soft-float)

```bash
# Install Ubuntu cross toolchain (soft-float)
sudo apt install gcc-arm-linux-gnueabi

# Build busybox
git clone https://git.busybox.net/busybox
cd busybox
git checkout 1_36_1   # 1.36 is the canonical version per BITACORA Cap 10

# Config: static, no float
make defconfig
sed -i 's|.*CONFIG_STATIC[ =].*|CONFIG_STATIC=y|' .config
sed -i 's|.*CONFIG_FEATURE_USE_BSS_TAIL.*|# CONFIG_FEATURE_USE_BSS_TAIL is not set|' .config
sed -i 's|.*CONFIG_FEATURE_SHARED_BUSYBOX.*|# CONFIG_FEATURE_SHARED_BUSYBOX is not set|' .config

# Compile with soft-float (gnueabi, NOT gnueabihf)
make CROSS_COMPILE=arm-linux-gnueabi- -j8

# Verify result is soft-float:
arm-linux-gnueabi-readelf -A busybox | grep -E "VFP|FP_arch"
# Expected: NOTHING (no VFP tags)
# If you see "Tag_ABI_VFP_args: VFP registers" → it's hard-float, REBUILD
```

The busybox currently in `tasks/00.01.eth-driver/initramfs/bin/busybox`
(May 2019, v1.31.0) is **HARD-FLOAT** and will crash certain applets as
PID 1. Replace with a soft-float build for clean operation.

## Verifying a binary's ABI

Always check before shipping:

```bash
arm-linux-gnueabi-readelf -A path/to/binary | grep -E "(VFP|FP_arch|Tag_ABI_FP)"
```

| Output | Meaning | Will it crash on H3600? |
|--------|---------|--------------------------|
| `(empty)` or only `Tag_ABI_FP_*` (no `_arch`/`_args`) | soft-float | ✅ runs fine |
| `Tag_FP_arch: VFPv2` | uses VFP | ⚠️ may crash |
| `Tag_ABI_VFP_args: VFP registers` | hard-float ABI | ❌ will SIGILL |
| `Tag_CPU_arch_profile: Application` + `Tag_CPU_arch: v7` | ARMv7 OK | (separate question) |

## Kernel module (.ko) for our mainline 6.6

Built in-tree as part of the kernel build (`linux-v6.6/`):

```bash
cd ~/Projects/MYSELF/ZTE/zxic/linux-v6.6
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- O=../build \
     drivers/net/ethernet/zte/zx279128-eth.ko -j8
```

The kernel itself is built with `CROSS_COMPILE=arm-linux-gnueabi-` for
consistency. Modules use the same.

**Verify**: `arm-linux-gnueabi-readelf -A linux-v6.6/drivers/.../zx279128-eth.ko`
should show *no VFP tags* on the .text section (it inherits the kernel's
ABI which is soft-float because mainline ARM kernel by default).

## Common gotchas (real bugs we hit)

1. **Hard-float busybox SIGILLs as PID 1** but works as child process — most
   applets don't hit VFP code, so it looks like the shell is "almost working"
   then dies mysteriously on `uname` / `date` / `dmesg` etc.
   → see `docs/SLOT_A_CSPD_PATCH_PLAYBOOK.md` for the path that led to this discovery
2. **dynamic-linked glibc binary** says `/tmp/x: not found` on stock device
   (stock uses uClibc with different linker path) → always static
3. **`nand write` writes more bytes than TFTP loaded** → trailing RAM garbage
   gets to NAND → CRC mismatch on next boot
   → see `tasks/00.01.eth-driver/scripts/build_slotA.py` header comment
4. **`flash_mainline.py` wait-after-TFTP was 45s** but TFTP took 75s
   → next U-Boot command sent mid-transfer, lost
   → fixed: bumped to 180s
5. **uImage entry vs load**: `-a 0x42000000 -e 0x42000040` (entry at +0x40 because
   uImage header is 64 B). Wrong entry → bootm hangs after "Starting kernel".
6. **DTB must be appended to zImage**, NOT passed as 3rd arg to bootm.
   ZTE U-Boot's bootm only supports 1 arg. See memory `[[h3600-kernel-boot-recipe]]`.
7. **PL011 DR is at offset +0x04**, not standard +0x00. CONFIG_ARCH_ZX=y handles
   this for kernel printk; userspace TTY writes might still be broken depending
   on kernel patch state. See memory `[[h3600-kernel-boot-recipe]]`.

## Where the working binaries are today

| What | Location | ABI | How built |
|------|----------|-----|-----------|
| `kmsg2uart` (UART daemon for stock kernel) | `tasks/00.02.stock-shell/out/kmsg2uart` | soft-float static (1.3 KB asm or 455 KB libc) | `arm-linux-gnueabi-gcc -nostdlib -static ... kmsg2uart_nolibc.S` |
| `/init` for mainline boot | `tasks/00.01.eth-driver/initramfs/init` | soft-float static | `arm-linux-gnueabi-gcc -static -O2 -s -o init init.c` |
| `zx279128-eth.ko` | `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.ko` | soft-float (kernel ABI) | in-tree kernel build with CROSS_COMPILE=arm-linux-gnueabi- |
| `busybox` (initramfs) | `tasks/00.01.eth-driver/initramfs/bin/busybox` | **HARD-FLOAT — TO BE REPLACED** | external download (May 2019), v1.31.0 |

## Quick smoke test

After cross-compiling something, send it to the device and verify:

```bash
# Stage via TFTP
cp my_binary tftp/my_binary

# On device (via UART REPL or stock SSH):
busybox tftp -g -r my_binary -l /tmp/my_binary 192.168.1.50
chmod +x /tmp/my_binary
/tmp/my_binary
# If SIGILL → rebuild with soft-float toolchain
```

## Related docs

- `tasks/00.02.stock-shell/README.md` — stock-traced rootfs build with cspd patch
- `docs/SLOT_A_CSPD_PATCH_PLAYBOOK.md` — full slot-A flash playbook + ZTE-shifted PL011
- `tasks/00.01.eth-driver/README.md` — mainline kernel + driver work
- `docs/NAND_LAYOUT_AND_BOOT.md` — NAND map + cspstart flow
- `BITACORA.md` Cap 10 — historical mainline boot work where this soft-float requirement was first discovered
