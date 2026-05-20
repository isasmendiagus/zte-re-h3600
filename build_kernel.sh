#!/usr/bin/env bash
# Build minimal Linux 6.6 kernel for ZTE H3600 (ZX279128S)
#
# Workflow:
#  1. Run setup_fork.sh to create v6.6 base with ZX296702 code revived
#  2. Apply our ZX279128S patches on top
#  3. Build zImage + DTB
#  4. mkimage to uImage
#  5. Copy to TFTP server
#
# Output: /srv/tftp/uImage  (loadable from U-Boot via tftp + bootm)

set -euo pipefail

PROJECT_ROOT=/home/ubuntu/Projects/MYSELF/ZTE
PATCHES=$PROJECT_ROOT/kernel-patches
FORK_DIR=$PROJECT_ROOT/linux-zxic-fork
TFTP_DIR=/srv/tftp

# Sanity check toolchain
need=(arm-linux-gnueabihf-gcc mkimage bison flex make)
for t in "${need[@]}"; do
    if ! command -v "$t" >/dev/null; then
        echo "ERROR: $t not installed. Run:"
        echo "  sudo apt-get install -y gcc-arm-linux-gnueabihf u-boot-tools bison flex libelf-dev libssl-dev"
        exit 1
    fi
done

# Step 1: Create v6.6 fork if not already done
if [ ! -d "$FORK_DIR" ]; then
    echo "==> [1/6] Creating v6.6 fork with ZX code revived..."
    cd "$PROJECT_ROOT"
    bash setup_fork.sh v6.6
    # this leaves us in $FORK_DIR with branch zxic-resurrect-v6.6
fi

cd "$FORK_DIR"

# Step 2: Apply our ZX279128S patches
echo "==> [2/6] Applying ZX279128S patches..."

# DTSI + DTS
mkdir -p arch/arm/boot/dts
cp "$PATCHES/dts/zx279128s.dtsi"      arch/arm/boot/dts/
cp "$PATCHES/dts/zx279128s-h3600.dts" arch/arm/boot/dts/

# Add to dts Makefile
DTSMK=arch/arm/boot/dts/Makefile
if ! grep -q zx279128s-h3600 "$DTSMK"; then
    # Find the zx section and append (or create new section)
    if grep -q "ARCH_ZX" "$DTSMK"; then
        sed -i '/dtb-\$(CONFIG_ARCH_ZX)/a\\tzx279128s-h3600.dtb \\' "$DTSMK"
    else
        printf '\ndtb-$(CONFIG_ARCH_ZX) += zx279128s-h3600.dtb\n' >> "$DTSMK"
    fi
fi

# clk driver
cp "$PATCHES/clk/clk-zx279128s.c" drivers/clk/zte/

# Add to drivers/clk/zte/Makefile
CLKMK=drivers/clk/zte/Makefile
if ! grep -q clk-zx279128s "$CLKMK"; then
    echo 'obj-$(CONFIG_SOC_ZX279128S) += clk-zx279128s.o' >> "$CLKMK"
fi

# mach-zx machine
cp "$PATCHES/mach-zx/zx279128s.c" arch/arm/mach-zx/

# Add to mach-zx Makefile
MACHMK=arch/arm/mach-zx/Makefile
if ! grep -q zx279128s "$MACHMK"; then
    echo 'obj-$(CONFIG_SOC_ZX279128S) += zx279128s.o' >> "$MACHMK"
fi

# Add SOC_ZX279128S to mach-zx Kconfig
MACHKC=arch/arm/mach-zx/Kconfig
if ! grep -q SOC_ZX279128S "$MACHKC"; then
    sed -i '/endif/i\
config SOC_ZX279128S\
	bool "ZTE ZX279128S (Cortex-A9 dual)"\
	default y\
	select ARM_GIC\
	select ARM_GLOBAL_TIMER\
	select HAVE_ARM_SCU if SMP\
	select HAVE_ARM_TWD if SMP\
	help\
	  Support for ZTE ZX279128S SoC (H3600 family).' "$MACHKC"
fi

# defconfig
cp "$PATCHES/configs/zx279128s_defconfig" arch/arm/configs/

# Step 3: Configure
echo "==> [3/6] Configuring kernel..."
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
make zx279128s_defconfig

# Step 4: Build
echo "==> [4/6] Building zImage + DTB ($(nproc) jobs)..."
make -j"$(nproc)" zImage dtbs

# Step 5: Append DTB to zImage and create uImage
echo "==> [5/6] Creating uImage..."
cat arch/arm/boot/zImage arch/arm/boot/dts/zx279128s-h3600.dtb \
    > /tmp/zImage_with_dtb

mkimage -A arm -O linux -T kernel -C none \
        -a 0x40008000 -e 0x40008000 \
        -n "ZX279128S H3600 mainline" \
        -d /tmp/zImage_with_dtb \
        /tmp/uImage

# Step 6: Deploy to TFTP
echo "==> [6/6] Deploying to TFTP..."
sudo cp /tmp/uImage "$TFTP_DIR/"
sudo chmod 644 "$TFTP_DIR/uImage"

ls -la "$TFTP_DIR/uImage"

cat <<EOF

==============================================================
Build complete. To boot from U-Boot:

  => setenv serverip 192.168.1.50
  => tftp 0x42000000 uImage
  => bootm 0x42000000

If you see kernel printk and 'Starting kernel...' followed by
PL011 init messages, we're alive.

If silent: kernel hung early. Use JTAG or earlier debug methods.
==============================================================
EOF
