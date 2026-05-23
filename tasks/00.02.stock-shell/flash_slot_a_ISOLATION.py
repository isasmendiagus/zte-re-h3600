#!/usr/bin/env python3
"""flash_slot_a_ISOLATION.py — flash ORIGINAL slot A bytes from NAND backup,
with a MATCHING CRC header.

Hypothesis test: is our `mkfs.jffs2`-produced JFFS2 the cause of the hang,
or is something else broken?

Method:
  1. Extract slot A rootfs region from h3600_nand_full.bin (untouched original)
  2. Compute its CRC32
  3. Build a header with that CRC (so cspstart accepts slot A strictly)
  4. Flash both via U-Boot in one session

If after flash slot A boots normally + SSH works → mkfs.jffs2 is the problem
                                                    (need different jffs2 strategy)
If slot A STILL hangs                              → flash mechanism issue
                                                    (re-evaluate everything)
"""
import sys, os, zlib
from pathlib import Path

THIS = Path(__file__).resolve().parent
ZXIC = THIS.parent.parent  # zxic/ root
sys.path.insert(0, str(ZXIC / "lib"))
import uart

NAND_DUMP = ZXIC / "ext" / "h3600_nand_full.bin"
TFTP = ZXIC / "tftp"

SLOT_A_ROOTFS_OFFSET = 0xa60000
SLOT_A_ROOTFS_SIZE   = 0x1620000
SLOT_A_HEADER_OFFSET = 0x2080000
SLOT_A_HEADER_SIZE   = 0x20000

ROOTFS_FILE = "isolation_original_enc.jffs2"
HEADER_FILE = "isolation_original_header.bin"

LOAD_ADDR = 0x42000000


def main():
    # 1. Extract ORIGINAL slot A rootfs from NAND backup
    nand = open(NAND_DUMP, 'rb').read()
    rootfs = nand[SLOT_A_ROOTFS_OFFSET:SLOT_A_ROOTFS_OFFSET + SLOT_A_ROOTFS_SIZE]
    rootfs_crc = zlib.crc32(rootfs) & 0xffffffff
    print(f"Extracted slot A rootfs: {len(rootfs):,} bytes, CRC32=0x{rootfs_crc:08x}")

    # 2. Extract ORIGINAL header
    header = bytearray(nand[SLOT_A_HEADER_OFFSET:SLOT_A_HEADER_OFFSET + SLOT_A_HEADER_SIZE])
    orig_rootfs_crc = int.from_bytes(header[0x48:0x4c], 'little')
    orig_header_crc = int.from_bytes(header[0xa4:0xa8], 'little')
    print(f"Original header rootfs CRC: 0x{orig_rootfs_crc:08x}")
    print(f"Original header self-CRC:   0x{orig_header_crc:08x}")

    # 3. Patch header with our COMPUTED CRC (matches actual rootfs)
    header[0x48:0x4c] = rootfs_crc.to_bytes(4, 'little')
    new_header_crc = zlib.crc32(bytes(header[0:0xa4])) & 0xffffffff
    header[0xa4:0xa8] = new_header_crc.to_bytes(4, 'little')
    print(f"New header rootfs CRC:      0x{rootfs_crc:08x}")
    print(f"New header self-CRC:        0x{new_header_crc:08x}")

    # 4. Write to TFTP
    (TFTP / ROOTFS_FILE).write_bytes(rootfs)
    (TFTP / HEADER_FILE).write_bytes(bytes(header))
    print(f"Staged: {TFTP / ROOTFS_FILE} ({len(rootfs):,} bytes)")
    print(f"Staged: {TFTP / HEADER_FILE} ({len(header):,} bytes)")

    # 5. Drive U-Boot to flash both
    print()
    print("=" * 70)
    print("Flashing ORIGINAL slot A bytes + matching header")
    print("=" * 70)
    print()

    seq = uart._PREAMBLE + [
        (f"tftp 0x{LOAD_ADDR:x} {ROOTFS_FILE}", (b"Bytes transferred", 240)),
        (f"nand erase 0x{SLOT_A_ROOTFS_OFFSET:x} 0x{SLOT_A_ROOTFS_SIZE:x}", (b"=>", 120)),
        (f"nand write 0x{LOAD_ADDR:x} 0x{SLOT_A_ROOTFS_OFFSET:x} 0x{SLOT_A_ROOTFS_SIZE:x}", (b"=>", 180)),
        (f"tftp 0x{LOAD_ADDR:x} {HEADER_FILE}", (b"Bytes transferred", 60)),
        (f"nand erase 0x{SLOT_A_HEADER_OFFSET:x} 0x{SLOT_A_HEADER_SIZE:x}", (b"=>", 30)),
        (f"nand write 0x{LOAD_ADDR:x} 0x{SLOT_A_HEADER_OFFSET:x} 0x{SLOT_A_HEADER_SIZE:x}", (b"=>", 60)),
        ("reset", 180),
    ]

    return uart._do_reset_then(seq) or 0


if __name__ == "__main__":
    sys.exit(main())
