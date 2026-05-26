# QEMU iteration scaffold (PARALLEL build target)

For fast iteration on **software-only** problems (zte_shim stub
signatures, struct offsets, init script bugs, kmod load order). Not
useful past the first MMIO access into ZX peripherals.

## Why parallel

Our stockport kernel hard-codes:
- `CONFIG_ARCH_ZX279128S=y` (mach-zx with ZX static iomap)
- `CONFIG_DEBUG_LL_UART_PHYS=0x94404000` (ZX-shifted PL011)
- PHYS_OFFSET=0x40000000 with appended DTB compat "zte,zx279128s"

None of those line up with `qemu-system-arm -M vexpress-a9`'s memory
map. Booting our existing zImage in qemu gives a silent boot — DEBUG_LL
writes vanish into unmapped MMIO, the pl011 driver can't find its DT
node, no console output, can't see anything.

## Build plan (TODO when first invoked)

Build a SECOND kernel from the same `linux-4.1.25/` tree:

```sh
# Config: start from vexpress_defconfig
make ARCH=arm CROSS_COMPILE=arm-buildroot-linux-gnueabihf- O=build-qemu vexpress_defconfig
# Override: CONFIG_INITRAMFS_SOURCE=/tmp/initramfs_stockport (same as device)
# Override: CONFIG_DEBUG_LL_INCLUDE=debug/pl01x.S
# Override: CONFIG_DEBUG_UART_PHYS=0x10009000 (vexpress PL011)
# Override: CONFIG_DEBUG_UART_VIRT=0xf8009000
make -j$(nproc) zImage modules
```

Boot:
```sh
qemu-system-arm \
  -M vexpress-a9 -m 256M \
  -kernel build-qemu/arch/arm/boot/zImage \
  -dtb build-qemu/arch/arm/boot/dts/vexpress-v2p-ca9.dtb \
  -append "console=ttyAMA0,115200 earlycon=pl011,0x10009000 earlyprintk loglevel=15 mem=256M rdinit=/init" \
  -nographic
```

## What this gets us

✓ Validates initramfs structure + `/init` script
✓ Validates zte_shim symbol surface (insmod succeeds/fails by signature)
✓ Catches struct-offset crashes in switch.ko's sw_init_switch
✓ Iterates in ~30 sec vs ~5 min device cycle

## What this DOESN'T get us

✗ Anything touching ZX MMIO (plat-zxylzb_9128S init_module crashes
  immediately when trying to of_iomap pon/npp/tm/pp/idm nodes that
  don't exist in vexpress DT)
✗ Real PHY / RX / TX traffic
✗ IRQ behavior matching ZX SoC

## Status

**NOT BUILT YET** — created as scaffold during 2026-05-26 stockport
revival. Activate when the iteration speed on device becomes the
bottleneck (i.e. when we're stuck in a multi-hour grind on shim
signatures or struct layouts).
