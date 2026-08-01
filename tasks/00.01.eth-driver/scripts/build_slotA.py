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
# Bumped 0xb→0xc→0xe→0x110 on 2026-08-01 when kernel + initramfs grew past 15 MiB.
# header[0x34] is set to this exact value so cspstart CRCs ONLY what we wrote,
# never the erased-but-untouched region beyond.
NAND_WRITE_SIZE = 0x1100000

LOAD_ADDR  = nl.RAM_LOAD_ADDR
ENTRY_ADDR = nl.RAM_LOAD_ADDR + 0x40


def run(cmd, cwd=None):
    print(f"  $ {cmd if isinstance(cmd, str) else ' '.join(cmd)}")
    subprocess.run(cmd, shell=isinstance(cmd, str), check=True, cwd=cwd)


def main():
    TFTP.mkdir(parents=True, exist_ok=True)

    # 0a) [Phase 1.1] Ensure the netfilter/NAT/conntrack config fragment is
    #     merged into the build .config. The build dir is untracked/ephemeral,
    #     so without this a fresh build would silently drop netfilter (CONFIG_
    #     NETFILTER is off in the base defconfig). merge_config.sh -m is a pure
    #     text merge (idempotent); olddefconfig then resolves dependencies.
    cfg  = BUILD / ".config"
    frag = ZXIC / "tasks/00.01.eth-driver/configs/netfilter.fragment"
    if cfg.exists() and frag.exists():
        print("  $ merge netfilter.fragment into .config (Phase 1.1)")
        run(["linux-v6.6/scripts/kconfig/merge_config.sh", "-m",
             "-O", str(BUILD), str(cfg), str(frag)], cwd=str(ZXIC))
        run(["make", "-C", str(ZXIC / "linux-v6.6"),
             "ARCH=arm", "CROSS_COMPILE=arm-linux-gnueabi-",
             f"O={BUILD}", "olddefconfig"])
        # Disable regulatory DB signature check — the initramfs regulatory.db
        # may not match the kernel's built-in certificates. Must also enable
        # CERTIFICATION_ONUS first, otherwise REQUIRE_SIGNED_REGDB is a hardcoded
        # def_bool y that can't be overridden.
        run([str(ZXIC / "linux-v6.6/scripts/config"),
             "--file", str(BUILD / ".config"),
             "--enable", "CFG80211_CERTIFICATION_ONUS"], cwd=str(ZXIC))
        run([str(ZXIC / "linux-v6.6/scripts/config"),
             "--file", str(BUILD / ".config"),
             "--disable", "CFG80211_REQUIRE_SIGNED_REGDB"], cwd=str(ZXIC))

    # 0) FULL kernel rebuild — always. Previously we tried to gate this on
    #    'is zx279128-eth.c newer than the .ko?' but that missed changes to
    #    any other in-tree driver we author (mdio-zte.c, future phy-zte.c,
    #    dsa/zte/*.c, …) and silently shipped a stale image. With kbuild's
    #    incremental build, doing `make all` here costs ~5 seconds when
    #    nothing changed — well worth the never-stale guarantee.
    print("  $ make all (kernel + modules + dtbs + zImage)")
    run(["make", "-C", str(ZXIC / "linux-v6.6"),
         "ARCH=arm", "CROSS_COMPILE=arm-linux-gnueabi-",
         f"O={BUILD}", "-j8", "all"])

    # 0b) Copy our task-local module into the initramfs source (it ships
    #     inside the kernel image via CONFIG_INITRAMFS_SOURCE).
    initramfs_ko_dst = Path("/tmp/initramfs_extract/lib/modules/zx279128-eth.ko")
    ko_src = BUILD / "drivers/net/ethernet/zte/zx279128-eth.ko"
    initramfs_ko_dst.parent.mkdir(parents=True, exist_ok=True)
    shutil = __import__("shutil")
    shutil.copy2(str(ko_src), str(initramfs_ko_dst))
    print(f"  ✓ copied {ko_src.name} → {initramfs_ko_dst}")

    # 0b2) Copy ALL kernel modules from the build tree into the initramfs,
    #     so version magic always matches. (cfg80211, mac80211, mt76, mt7915e, …)
    import glob as _glob
    initramfs_mod_dir = Path("/tmp/initramfs_extract/lib/modules")
    initramfs_mod_src = ZXIC / "tasks/00.01.eth-driver/initramfs/lib/modules"
    for ko_pattern in ["drivers/net/wireless/**/*.ko", "net/wireless/*.ko",
                         "net/mac80211/*.ko", "drivers/pci/controller/dwc/*.ko",
                         "drivers/usb/dwc3/*.ko", "drivers/usb/host/xhci*.ko",
                         "drivers/usb/storage/*.ko"]:
        for ko in _glob.glob(str(BUILD / ko_pattern), recursive=True):
            dst = initramfs_mod_dir / Path(ko).name
            shutil.copy2(ko, str(dst))
        for ko in _glob.glob(str(BUILD / ko_pattern), recursive=True):
            dst = initramfs_mod_src / Path(ko).name
            shutil.copy2(ko, str(dst))

    # 0c) Re-embed the (possibly updated) initramfs by rebuilding zImage.
    #     Cheap when initramfs hash didn't change.
    print("  $ make zImage (re-embed initramfs)")
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
