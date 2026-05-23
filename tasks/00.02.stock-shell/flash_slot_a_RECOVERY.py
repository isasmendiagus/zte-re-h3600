#!/usr/bin/env python3
"""flash_slot_a_RECOVERY.py — Restore slot A to factory-stock state.

Use this if slot A is broken (hung kernel boot, etc.) and you want to
revert to factory bytes extracted from h3600_nand_full.bin.

What it flashes (from ../tftp/):
  - rootfs_a_ORIGINAL_enc.jffs2  (encrypted stock rootfs)
  - header_a_ORIGINAL.bin         (stock BootPara header)

After flash:
  - cspstart computes rootfs CRC (mismatch vs stored — this is normal for stock)
  - Falls through to "use defualt jffs2 fs!!" lenient path → accepts
  - Boots stock kernel + stock rootfs
  - Device returns to normal stock behavior

Slot B is never touched.
"""
import sys, os
from pathlib import Path

THIS = Path(__file__).resolve().parent
ZXIC = THIS.parent.parent  # zxic/ root
sys.path.insert(0, str(ZXIC / "lib"))
import uart

ROOTFS_FILE = "rootfs_a_ORIGINAL_enc.jffs2"
HEADER_FILE = "header_a_ORIGINAL.bin"

SLOT_A_ROOTFS_OFFSET = 0xa60000
SLOT_A_ROOTFS_SIZE   = 0x1620000
SLOT_A_HEADER_OFFSET = 0x2080000
SLOT_A_HEADER_SIZE   = 0x20000

LOAD_ADDR = 0x42000000


def main():
    tftp = ZXIC / "tftp"
    for f in (ROOTFS_FILE, HEADER_FILE):
        p = tftp / f
        if not p.exists():
            print(f"ERROR: {p} missing", file=sys.stderr)
            sys.exit(2)
        print(f"  staged: {p} ({p.stat().st_size:,} bytes)")

    print()
    print("=" * 70)
    print("RESTORING slot A from factory NAND backup")
    print("Slot B untouched.")
    print("=" * 70)
    print()

    seq = uart._PREAMBLE + [
        # 1. Flash original rootfs
        (f"tftp 0x{LOAD_ADDR:x} {ROOTFS_FILE}",
         (b"Bytes transferred", 240)),
        (f"nand erase 0x{SLOT_A_ROOTFS_OFFSET:x} 0x{SLOT_A_ROOTFS_SIZE:x}",
         (b"=>", 120)),
        (f"nand write 0x{LOAD_ADDR:x} 0x{SLOT_A_ROOTFS_OFFSET:x} "
         f"0x{SLOT_A_ROOTFS_SIZE:x}",
         (b"=>", 180)),

        # 2. Flash original header (CRCs match factory)
        (f"tftp 0x{LOAD_ADDR:x} {HEADER_FILE}",
         (b"Bytes transferred", 60)),
        (f"nand erase 0x{SLOT_A_HEADER_OFFSET:x} 0x{SLOT_A_HEADER_SIZE:x}",
         (b"=>", 30)),
        (f"nand write 0x{LOAD_ADDR:x} 0x{SLOT_A_HEADER_OFFSET:x} "
         f"0x{SLOT_A_HEADER_SIZE:x}",
         (b"=>", 60)),

        ("reset", 120),
    ]

    return uart._do_reset_then(seq) or 0


if __name__ == "__main__":
    sys.exit(main())
