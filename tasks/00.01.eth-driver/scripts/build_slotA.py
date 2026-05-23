#!/usr/bin/env python3
"""Build tftp/slotA.bin and tftp/header_A_modified.bin from a freshly-built
mainline kernel + its embedded initramfs.

THE BUG THIS FIXES (2026-05-22):
  The original inline builder produced slotA.bin = 11,010,829 bytes (32B
  wrapper + uImage). flash_mainline.py then does `nand write 0xb00000` =
  11,534,336 bytes from RAM, but TFTP only loads the actual file size into
  RAM. The extra ~523KB written to NAND is whatever RAM garbage happened
  to be there. Our CRC computation assumed `slotA[32:] + 0xff padding`
  (clean), so the on-NAND CRC mismatched at every boot, cspstart rejected
  slot A, and the device fell back to slot B (stock). Mainline never ran.

  Fix: pad slotA.bin to NAND_WRITE_SIZE (0xb00000) with 0xff BEFORE TFTP.
  Then the bytes on NAND exactly equal slotA.bin (no garbage), and our CRC
  computation is correct.

Outputs (in H3600/tftp/):
  - slotA.bin               (padded to NAND_WRITE_SIZE; 0xff trailer)
  - zImage_dtb.uimg         (kept for reference)
  - header_A_modified.bin   (BootPara with kernel CRC matching slotA.bin)
"""
import os, sys, subprocess, struct, zlib
from pathlib import Path

ZXIC = Path(__file__).resolve().parents[3]  # zxic/ root
BUILD = ZXIC / "build"
TFTP  = ZXIC / "tftp"
NAND  = ZXIC / "ext" / "h3600_nand_full.bin"

# NAND layout (per docs/NAND_LAYOUT_AND_BOOT.md)
SLOT_A_KERNEL_OFFSET = 0x700000
NAND_ERASE_SIZE      = 0x1980000   # full kernel-side erase region for slot A
NAND_WRITE_SIZE      = 0xb00000    # how much flash_mainline.py copies to NAND
# IMPORTANT: header[0x34] tells cspstart how many bytes to CRC. Setting it to
# our exact padded slotA size means cspstart CRCs ONLY what we wrote, never the
# erased-but-untouched region beyond. Removes ambiguity from bad-block skip /
# unknown padding in the gap. 0xb00000 = 11 MiB matches NAND_WRITE_SIZE.
KERNEL_SIZE_HDR      = NAND_WRITE_SIZE
SLOT_A_ROOTFS_SIZE   = 0x1620000
SLOT_A_HEADER_OFFSET = 0x2080000

# 32-byte ZTE wrapper (magic that cspstart recognizes)
ZTE_WRAPPER = (b"\x33\x33\x33\x33\xcc\xcc\xcc\xcc"
               b"\x88\x88\x88\x88\xdd\xdd\xdd\xdd"
               b"\xff" * 16)

LOAD_ADDR  = 0x42000000
ENTRY_ADDR = 0x42000040


def run(cmd, cwd=None):
    print(f"  $ {cmd if isinstance(cmd, str) else ' '.join(cmd)}")
    subprocess.run(cmd, shell=isinstance(cmd, str), check=True, cwd=cwd)


def main():
    TFTP.mkdir(parents=True, exist_ok=True)

    # 1) Concat zImage + DTB
    zimage = BUILD / "arch/arm/boot/zImage"
    dtb    = BUILD / "arch/arm/boot/dts/zte/zx279128s-h3600.dtb"
    if not zimage.exists() or not dtb.exists():
        sys.exit(f"missing build artifacts: {zimage} or {dtb}")
    concat = TFTP / "zImage_dtb.bin"
    concat.write_bytes(zimage.read_bytes() + dtb.read_bytes())
    print(f"  ✓ zImage+DTB concat: {concat.stat().st_size:,} bytes")

    # 2) Wrap as uImage
    uimg = TFTP / "zImage_dtb.uimg"
    run(["mkimage", "-A", "arm", "-O", "linux", "-T", "kernel", "-C", "none",
         "-a", f"0x{LOAD_ADDR:x}", "-e", f"0x{ENTRY_ADDR:x}",
         "-d", str(concat), str(uimg)])

    # 3) Build slotA.bin = 32B wrapper + uImage, PADDED with 0xff to NAND_WRITE_SIZE
    uimg_bytes = uimg.read_bytes()
    body = ZTE_WRAPPER + uimg_bytes
    if len(body) > NAND_WRITE_SIZE:
        sys.exit(f"slotA body ({len(body):#x}) exceeds NAND write size ({NAND_WRITE_SIZE:#x})")
    padded = body + b"\xff" * (NAND_WRITE_SIZE - len(body))
    slotA = TFTP / "slotA.bin"
    slotA.write_bytes(padded)
    print(f"  ✓ slotA.bin: {len(body):,} body + {NAND_WRITE_SIZE - len(body):,} 0xff pad "
          f"= {len(padded):,} bytes (0x{NAND_WRITE_SIZE:x})")

    # 4) Patch BootPara header for the new kernel
    #    cspstart reads NAND[0x700000 + 0 .. KERNEL_SIZE_HDR] and CRCs it. We
    #    intentionally include the 32-byte ZTE wrapper in the CRC region because
    #    that's the byte stream cspstart actually reads — verified by boot log
    #    "verify_kernel readflash @0x700000 size:..." which starts at 0x700000
    #    (the wrapper), NOT 0x700020.
    #    With KERNEL_SIZE_HDR = NAND_WRITE_SIZE, all CRCed bytes are our padded
    #    slotA.bin (no unknown beyond-write region).
    assert KERNEL_SIZE_HDR == NAND_WRITE_SIZE == len(padded)
    crc_region = padded
    kernel_crc = zlib.crc32(crc_region) & 0xffffffff
    rootfs_crc = zlib.crc32(b"\xff" * SLOT_A_ROOTFS_SIZE) & 0xffffffff  # rootfs erased

    nand_bytes = NAND.read_bytes()
    hdr = bytearray(nand_bytes[SLOT_A_HEADER_OFFSET:SLOT_A_HEADER_OFFSET + 0x20000])
    hdr[0x34:0x38] = struct.pack("<I", KERNEL_SIZE_HDR)
    hdr[0x3c:0x40] = struct.pack("<I", kernel_crc)
    hdr[0x48:0x4c] = struct.pack("<I", rootfs_crc)
    hdr[0xa4:0xa8] = struct.pack("<I", zlib.crc32(bytes(hdr[:0xa4])) & 0xffffffff)
    header_out = TFTP / "header_A_modified.bin"
    header_out.write_bytes(bytes(hdr))
    print(f"  ✓ header_A_modified.bin: kernel_size=0x{KERNEL_SIZE_HDR:x} "
          f"kernel_crc=0x{kernel_crc:08x} rootfs_crc=0x{rootfs_crc:08x}")

    print("\nReady to flash:")
    print(f"  cd {H3600}")
    print(f"  python3 flash_mainline.py")


if __name__ == "__main__":
    main()
