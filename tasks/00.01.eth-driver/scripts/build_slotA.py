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
import os, sys, subprocess
from pathlib import Path

ZXIC = Path(__file__).resolve().parents[3]  # zxic/ root
BUILD = ZXIC / "build"
TFTP  = ZXIC / "tftp"
NAND  = ZXIC / "ext" / "h3600_nand_full.bin"

# Canonical NAND layout + header/CRC helpers live in tasks/00.04.flash-tool/.
# Import them rather than duplicating: anything we change there propagates
# here automatically.
sys.path.insert(0, str(ZXIC / "tasks" / "00.04.flash-tool"))
import nand_layout as nl  # noqa: E402
import bootpara as bp     # noqa: E402

SLOT = nl.SLOT_A

# How many bytes we actually flash into the kernel region (≤ slot kernel_max_size).
# Bumped 0xb→0xc on 2026-05-24 when kernel + initramfs grew past 11 MiB.
# header[0x34] is set to this exact value so cspstart CRCs ONLY what we wrote,
# never the erased-but-untouched region beyond.
NAND_WRITE_SIZE = 0xc00000

LOAD_ADDR  = nl.RAM_LOAD_ADDR
ENTRY_ADDR = nl.RAM_LOAD_ADDR + 0x40


def run(cmd, cwd=None):
    print(f"  $ {cmd if isinstance(cmd, str) else ' '.join(cmd)}")
    subprocess.run(cmd, shell=isinstance(cmd, str), check=True, cwd=cwd)


def main():
    TFTP.mkdir(parents=True, exist_ok=True)

    # 0) CRITICAL: refresh the driver module into the initramfs source the
    #    kernel embeds, then rebuild zImage. CONFIG_ZX279128_ETH=m means
    #    the .ko ships inside the initramfs (path from .config
    #    CONFIG_INITRAMFS_SOURCE), NOT linked into vmlinux. Without this
    #    step, edits to zx279128-eth.c never reach the device — the
    #    kernel boots the .ko snapshot from the last manual copy. We lost
    #    several hours of testing to this 2026-05-25; never again.
    initramfs_ko_dst = Path("/tmp/initramfs_extract/lib/modules/zx279128-eth.ko")
    ko_src = BUILD / "drivers/net/ethernet/zte/zx279128-eth.ko"
    if not ko_src.exists() or ko_src.stat().st_mtime < \
            (ZXIC / "linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c").stat().st_mtime:
        print("  $ make zx279128-eth.ko (driver .c changed since last build)")
        run(["make", "-C", str(ZXIC / "linux-v6.6"),
             "ARCH=arm", "CROSS_COMPILE=arm-linux-gnueabi-",
             f"O={BUILD}", "-j8",
             "drivers/net/ethernet/zte/zx279128-eth.ko"])
    if initramfs_ko_dst.exists() and \
            initramfs_ko_dst.stat().st_mtime >= ko_src.stat().st_mtime:
        print(f"  ✓ initramfs .ko already up to date")
    else:
        initramfs_ko_dst.parent.mkdir(parents=True, exist_ok=True)
        shutil = __import__("shutil")
        shutil.copy2(str(ko_src), str(initramfs_ko_dst))
        print(f"  ✓ copied {ko_src.name} → {initramfs_ko_dst}")
        # 0b) Rebuild zImage to re-embed the updated initramfs.
        print("  $ make zImage (re-embed updated initramfs)")
        run(["make", "-C", str(ZXIC / "linux-v6.6"),
             "ARCH=arm", "CROSS_COMPILE=arm-linux-gnueabi-",
             f"O={BUILD}", "-j8", "zImage"])

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
    body = nl.ZTE_KERNEL_WRAPPER + uimg_bytes
    if len(body) > NAND_WRITE_SIZE:
        sys.exit(f"slotA body ({len(body):#x}) exceeds NAND write size ({NAND_WRITE_SIZE:#x})")
    padded = bp.pad_with_ff(body, NAND_WRITE_SIZE)
    slotA = TFTP / "slotA.bin"
    slotA.write_bytes(padded)
    print(f"  ✓ slotA.bin: {len(body):,} body + {NAND_WRITE_SIZE - len(body):,} 0xff pad "
          f"= {len(padded):,} bytes (0x{NAND_WRITE_SIZE:x})")

    # 4) Patch BootPara header for the new kernel
    #    cspstart reads NAND[kernel_offset .. kernel_offset+kernel_size_hdr]
    #    and CRCs it. We include the 32-byte ZTE wrapper in the CRC region
    #    because that's the byte stream cspstart actually reads — verified
    #    by boot log "verify_kernel readflash @0x700000 size:...". With
    #    kernel_size_hdr == NAND_WRITE_SIZE, every CRCed byte is our padded
    #    slotA.bin (no unknown beyond-write region).
    kernel_crc = bp.csp_crc(padded)
    rootfs_crc = bp.csp_crc(b"\xff" * SLOT.rootfs_size)  # rootfs erased

    nand_bytes = NAND.read_bytes()
    hdr_old = nand_bytes[SLOT.header_offset:SLOT.header_offset + SLOT.header_size]
    hdr_new = bp.patch_both(hdr_old,
                            kernel_size=len(padded),
                            kernel_crc=kernel_crc,
                            rootfs_crc=rootfs_crc)
    header_out = TFTP / "header_A_modified.bin"
    header_out.write_bytes(hdr_new)
    print(f"  ✓ header_A_modified.bin: kernel_size=0x{len(padded):x} "
          f"kernel_crc=0x{kernel_crc:08x} rootfs_crc=0x{rootfs_crc:08x}")

    print("\nReady to flash:")
    print(f"  cd {ZXIC}")
    print(f"  python3 tasks/00.01.eth-driver/scripts/flash_mainline.py")
    print(f"\nReady to TFTP-boot (no NAND write):")
    print(f"  python3 tasks/00.01.eth-driver/scripts/tftp_boot_mainline.py")


if __name__ == "__main__":
    main()
