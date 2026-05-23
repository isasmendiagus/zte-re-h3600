#!/usr/bin/env bash
#
# build.sh — Build the ZX279128S stockport kernel 4.1.25 + zte_shim.ko + deploy
#
# Usage:
#   ./build.sh              # full: shim + kernel + deploy
#   ./build.sh shim         # only shim
#   ./build.sh kernel       # only kernel
#   ./build.sh deploy       # only copy uImage to TFTP root
#   ./build.sh clean        # mrproper kernel + clean shim
#
# Critical knobs (DO NOT regress without testing):
#   - Toolchain:   ~/toolchains/armv7-eabihf--glibc--stable-2018.11-1 (Buildroot GCC 7.3)
#                  Newer GCC (e.g. system 13.x) breaks 4.1.25 asm macros and lacks
#                  armv7-a support on hard-float ABI.
#   - LOADADDR:    0x40008000 (stock ZTE convention; mainline 0x42000000 hangs bootm)
#   - PHYS_OFFSET: 0x40000000 (must be set; ARM_PATCH_PHYS_VIRT default-off in our cfg)
#   - ARCH_ZX:     y           (provides mach-zx + DEBUG_LL PL011 shifted offsets;
#                               olddefconfig will silently turn this off — re-pin)
#   - UNINLINE_SPIN_UNLOCK: y  (else stock .ko can't resolve _raw_spin_unlock)
#   - INITRAMFS_SOURCE: /tmp/initramfs_stockport (bundles init + .ko's into uImage)
#
# Kernel patches applied (4 added EXPORT_SYMBOLs for stock .ko compatibility):
#   - kernel/kallsyms.c       : EXPORT_SYMBOL(kallsyms_lookup)
#   - kernel/pid.c            : EXPORT_SYMBOL(find_task_by_vpid)
#   - arch/arm/kernel/traps.c : EXPORT_SYMBOL(show_stack)
#   - .config                 : CONFIG_UNINLINE_SPIN_UNLOCK=y  → exports _raw_spin_unlock
#
set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
KERNEL_DIR="$ROOT/linux-4.1.25"
SHIM_DIR="$ROOT/zte_shim"
TFTP_DIR="$HOME/Projects/MYSELF/ZTE/zxic/tftp"
INITRAMFS_DIR="/tmp/initramfs_stockport"

TOOLCHAIN_PREFIX="$HOME/toolchains/armv7-eabihf--glibc--stable-2018.11-1"
export PATH="$TOOLCHAIN_PREFIX/bin:$PATH"
export ARCH=arm
export CROSS_COMPILE=arm-buildroot-linux-gnueabihf-
export LOADADDR=0x40008000

NCPUS="$(nproc)"

check_toolchain() {
	if ! command -v ${CROSS_COMPILE}gcc >/dev/null 2>&1; then
		echo "ERROR: missing $TOOLCHAIN_PREFIX/bin/${CROSS_COMPILE}gcc" >&2
		echo "Download from: https://toolchains.bootlin.com/downloads/releases/toolchains/armv7-eabihf/tarballs/" >&2
		echo "  tarball: armv7-eabihf--glibc--stable-2018.11-1.tar.bz2 (GCC 7.3, glibc, Buildroot)" >&2
		exit 1
	fi
	echo "[build] toolchain: $(${CROSS_COMPILE}gcc --version | head -1)"
}

check_initramfs() {
	if [ ! -d "$INITRAMFS_DIR" ]; then
		echo "ERROR: initramfs dir missing: $INITRAMFS_DIR" >&2
		echo "Re-extract from a known good rootfs or build via scripts/gen_initramfs.sh" >&2
		exit 1
	fi
	for f in init lib/modules/4.1.25/zte_shim.ko lib/modules/4.1.25/zx_ponreg.ko \
		 lib/modules/4.1.25/plat-zxylzb_9128S.ko lib/modules/4.1.25/tm.ko \
		 lib/modules/4.1.25/switch.ko; do
		[ -e "$INITRAMFS_DIR/$f" ] || echo "[warn] initramfs missing: $f"
	done
}

pin_config() {
	cd "$KERNEL_DIR"
	# Pin the knobs olddefconfig regresses or leaves unset.
	#
	# Symbol names match stock /etc/autokernelconf (2026-05-21 discovery):
	#   ARCH_ZX279128S (NOT ARCH_ZX)  → mach-zx code compiled in
	#   MACH_ZX279128S (NOT SOC_*)    → machine scaffolding
	#   DEBUG_LL family               → early UART output via pl01x.S
	# Strip the old names if any leftover from prior builds:
	sed -i '/^CONFIG_ARCH_ZX=y$/d;        /^CONFIG_SOC_ZX279128S=y$/d' .config
	sed -i '/^# CONFIG_ARCH_ZX is not set$/d' .config
	# Pin the new (correct) names. olddefconfig will preserve them because
	# CONFIG_ARCH_ZX279128S has prompt-when-MULTI_V7 dependency.
	grep -q "^CONFIG_ARCH_ZX279128S=y$" .config || echo "CONFIG_ARCH_ZX279128S=y" >> .config
	grep -q "^CONFIG_MACH_ZX279128S=y$" .config || echo "CONFIG_MACH_ZX279128S=y" >> .config
	# DEBUG_LL — gives early UART output through ZTE-patched pl01x.S BEFORE
	# the rest of the kernel console driver is up. Without it: silent boot.
	grep -q "^CONFIG_DEBUG_LL=y$" .config || echo "CONFIG_DEBUG_LL=y" >> .config
	grep -q "^CONFIG_DEBUG_LL_UART_PL01X=y$" .config || echo "CONFIG_DEBUG_LL_UART_PL01X=y" >> .config
	grep -q "^CONFIG_DEBUG_UART_PHYS=0x94404000$" .config || {
		sed -i '/^CONFIG_DEBUG_UART_PHYS=/d' .config
		echo "CONFIG_DEBUG_UART_PHYS=0x94404000" >> .config
	}
	grep -q "^CONFIG_DEBUG_UART_VIRT=0xf0704000$" .config || {
		sed -i '/^CONFIG_DEBUG_UART_VIRT=/d' .config
		echo "CONFIG_DEBUG_UART_VIRT=0xf0704000" >> .config
	}
	grep -q '^CONFIG_DEBUG_LL_INCLUDE="debug/pl01x.S"$' .config || {
		sed -i '/^CONFIG_DEBUG_LL_INCLUDE=/d' .config
		echo 'CONFIG_DEBUG_LL_INCLUDE="debug/pl01x.S"' >> .config
	}
	grep -q "^CONFIG_EARLY_PRINTK=y$" .config || echo "CONFIG_EARLY_PRINTK=y" >> .config
	# APPENDED DTB + ATAG_DTB_COMPAT match stock. ATAG_DTB_COMPAT lets the
	# bootloader's ATAG cmdline override DTB chosen/bootargs (per stock
	# /etc/autokernelconf: CONFIG_ARM_ATAG_DTB_COMPAT_CMDLINE_FROM_BOOTLOADER=y).
	grep -q "^CONFIG_ARM_APPENDED_DTB=y$" .config || {
		sed -i '/^# CONFIG_ARM_APPENDED_DTB is not set$/d' .config
		echo "CONFIG_ARM_APPENDED_DTB=y" >> .config
	}
	grep -q "^CONFIG_ARM_ATAG_DTB_COMPAT=y$" .config || {
		sed -i '/^# CONFIG_ARM_ATAG_DTB_COMPAT is not set$/d' .config
		echo "CONFIG_ARM_ATAG_DTB_COMPAT=y" >> .config
		echo "CONFIG_ARM_ATAG_DTB_COMPAT_CMDLINE_FROM_BOOTLOADER=y" >> .config
	}
	# CONFIG_UNINLINE_SPIN_UNLOCK no longer pinned: olddefconfig resets it
	# (depends on ARCH_INLINE_SPIN_UNLOCK_* on ARM). Instead, spinlock.c
	# was patched to unconditionally export _raw_spin_unlock.
	grep -qE "^CONFIG_PHYS_OFFSET=0x[0-9a-fA-F]+$" .config || {
		sed -i '/^CONFIG_PHYS_OFFSET=/d' .config
		echo "CONFIG_PHYS_OFFSET=0x40000000" >> .config
	}
	grep -q "^CONFIG_INITRAMFS_SOURCE=\"$INITRAMFS_DIR\"" .config || {
		sed -i "s|^CONFIG_INITRAMFS_SOURCE=.*|CONFIG_INITRAMFS_SOURCE=\"$INITRAMFS_DIR\"|" .config
	}
	make olddefconfig >/dev/null 2>&1 || true
	# Verify pins survived olddefconfig
	for k in CONFIG_ARCH_ZX279128S=y CONFIG_MACH_ZX279128S=y CONFIG_DEBUG_LL=y \
		 CONFIG_DEBUG_LL_UART_PL01X=y CONFIG_DEBUG_UART_PHYS=0x94404000 \
		 CONFIG_DEBUG_UART_VIRT=0xf0704000; do
		grep -q "^$k\$" .config || { echo "ERROR: $k did not survive olddefconfig" >&2; exit 1; }
	done
	grep -q '^CONFIG_DEBUG_LL_INCLUDE="debug/pl01x.S"$' .config || \
		{ echo "ERROR: DEBUG_LL_INCLUDE not pl01x.S" >&2; exit 1; }
	grep -q "^CONFIG_PHYS_OFFSET=0x40000000\$" .config || \
		{ echo "ERROR: PHYS_OFFSET unpinned" >&2; exit 1; }
}

check_dtb_in_tftp() {
	# The kernel goes silent without a DTB (mach-zx static UART iomap
	# never gets installed). bootm MUST be invoked as:
	#   bootm 0x42000000 - 0x44000000
	# where 0x44000000 holds h3600_stockport.dtb. uart.py auto_bootm_stockport
	# already does this — but ensure the DTB file is present.
	if [ ! -f "$TFTP_DIR/h3600_stockport.dtb" ]; then
		echo "ERROR: missing $TFTP_DIR/h3600_stockport.dtb" >&2
		echo "Without a DTB the kernel will boot silent (no UART after MMU enable)." >&2
		echo "Build via: dtc -I dts -O dtb -o $TFTP_DIR/h3600_stockport.dtb <h3600_stockport.dts>" >&2
		exit 1
	fi
}

build_kernel() {
	check_toolchain
	check_initramfs
	cd "$KERNEL_DIR"
	pin_config
	# Stock uses zImage with APPENDED DTB, wrapped as uImage, AND
	# CONFIG_ARM_ATAG_DTB_COMPAT=y so the cmdline+memory from bootloader's
	# ATAGs are merged into the DT at boot time. This is the only way the
	# DT-based machine (`DT_MACHINE_START` with `compatible = "zte,zx279128s"`)
	# can be selected AND get init_time / init_machine callbacks for clock,
	# GIC, timer, etc — without writing all that by hand in mach-zx.
	echo "[build] kernel zImage (-j$NCPUS) ..."
	time make -j"$NCPUS" zImage
	local DTB="$TFTP_DIR/h3600_stockport.dtb"
	[ -f "$DTB" ] || { echo "ERROR: missing DTB at $DTB — build it first" >&2; exit 1; }
	cat arch/arm/boot/zImage "$DTB" > arch/arm/boot/zImage_dtb.bin
	mkimage -A arm -O linux -C none -T kernel -a 0x40008000 -e 0x40008000 \
		-n "ZX279128S stockport+dtb" \
		-d arch/arm/boot/zImage_dtb.bin arch/arm/boot/uImage >/dev/null
	ls -la arch/arm/boot/uImage
}

build_shim() {
	check_toolchain
	cd "$SHIM_DIR"
	make clean >/dev/null 2>&1 || true
	echo "[build] zte_shim.ko ..."
	make -j"$NCPUS"
	N=$(${CROSS_COMPILE}nm zte_shim.ko | grep -c " [TD] ")
	echo "[build] shim exports: $N (expected ~40; >50 means duplicates with stock .ko)"
	cp zte_shim.ko "$INITRAMFS_DIR/lib/modules/4.1.25/zte_shim.ko"
	echo "[build] shim installed to $INITRAMFS_DIR"
}

deploy() {
	[ -f "$KERNEL_DIR/arch/arm/boot/uImage" ] || { echo "ERROR: build kernel first" >&2; exit 1; }
	mkdir -p "$TFTP_DIR"
	cp "$KERNEL_DIR/arch/arm/boot/uImage" "$TFTP_DIR/uImage_stockport"
	ls -la "$TFTP_DIR/uImage_stockport"
	echo "[deploy] ready: boot via 'uart.py auto_bootm_stockport'"
	echo "[deploy] note: zImage has APPENDED DTB (CONFIG_ARM_APPENDED_DTB=y)"
	echo "         + ATAG_DTB_COMPAT merges bootloader cmdline into DT."
	echo "         bootm is single-arg: 'bootm 0x42000000' (DTB is inside)"
}

clean() {
	cd "$SHIM_DIR" && make clean >/dev/null 2>&1 || true
	cd "$KERNEL_DIR" && make mrproper
	echo "[clean] done — restore .config from .config.prev before rebuilding"
}

case "${1:-all}" in
	shim)    build_shim ;;
	kernel)  build_kernel ;;
	deploy)  deploy ;;
	clean)   clean ;;
	all|"")  build_shim; build_kernel; deploy ;;
	*)       echo "Usage: $0 [shim|kernel|deploy|clean|all]" >&2; exit 2 ;;
esac
