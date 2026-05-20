#!/bin/bash
# Re-copy build artifacts into the TFTP dir.
# Run after every kernel rebuild.
set -e
BUILD=/home/ubuntu/Projects/MYSELF/ZTE/H3600/build
TFTP=/home/ubuntu/Projects/MYSELF/ZTE/H3600/tftp

cp -f "$BUILD/arch/arm/boot/zImage"                          "$TFTP/zImage"
cp -f "$BUILD/arch/arm/boot/dts/zte/zx279128s-h3600.dtb"     "$TFTP/h3600.dtb"
if [ -f /tmp/initramfs.cpio.gz ]; then
  cp -f /tmp/initramfs.cpio.gz "$TFTP/initramfs.cpio.gz"
  mkimage -A arm -O linux -T ramdisk -C gzip \
    -a 0x45000000 -e 0x45000000 \
    -n "H3600 initramfs" \
    -d /tmp/initramfs.cpio.gz "$TFTP/uInitrd" >/dev/null
fi

ls -la "$TFTP"
