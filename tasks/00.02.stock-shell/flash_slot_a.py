#!/usr/bin/env python3
"""flash_slot_a.py — Drive U-Boot via UART to flash rootfs + header in ONE session.

NAND LAYOUT (touched by this script):
  0x00a60000 — slot A rootfs (22 MiB JFFS2, AES-128-ECB encrypted)
  0x02080000 — slot A BootPara header (128 KiB; we rewrite with new rootfs CRC)
DO NOT TOUCH:
  0x00000000-0x000bffff — bootloader (BRICK risk)
  0x00700000-0x025fffff — slot A kernel region (we keep stock kernel here)
  0x02700000+           — slot B (factory recovery fallback)
Full NAND map + flash invariants: see tasks/00.03.nand-flash/README.md.

Prerequisite: run `./prepare_slot_a.sh` first to produce the files in zxic/tftp/.

What this does:
  1. DTR-reset the device
  2. Drive past "Press 1" + password prompt → U-Boot `=>` prompt
  3. Set TFTP server IP
  4. TFTP-pull encrypted rootfs → nand erase + write to 0xa60000 (slot A rootfs)
  5. TFTP-pull patched header  → nand erase + write to 0x2080000 (slot A header)
  6. reset
  7. Stream UART for ~3 min to capture boot — looks for:
       - "verify fs success!!" (slot A passed CRC → patch worked)
       - "Romfs CRC check failed" (slot A still failed → fell back to slot B)
       - eventual login prompt or persistent printk

CRC INVARIANTS:
  header[0x48] = LE u32 zlib.crc32(encrypted rootfs JFFS2)
  header[0xa4] = LE u32 zlib.crc32(header[0:0xa4])
  Rootfs CRC is LENIENT (cspstart accepts on JFFS2 magic if strict mismatches).
  csp_crc log prints (A, ~A); store A.

Why one session: each boot causes JFFS2 to mutate NAND bytes (mount counter etc.)
which drifts the rootfs CRC. By flashing rootfs and updated header back-to-back
without booting between them, both end up consistent.

DOES NOT modify slot B (intact fallback). Reversible via ext/h3600_nand_full.bin.

Usage:
    python3 flash_slot_a.py           # full flash + monitor
    python3 flash_slot_a.py --dry-run # just print what it would do
"""
import os, sys, time, argparse, threading
from pathlib import Path

# Reuse uart.py from zxic/lib/ (we are at zxic/tasks/00.02.stock-shell/)
THIS = Path(__file__).resolve().parent
ZXIC = THIS.parent.parent  # zxic/ root
sys.path.insert(0, str(ZXIC / "lib"))
import uart                                  # noqa: E402

# ---------- config ----------
ROOTFS_FILE = "rootfs_a_patched_enc.jffs2"   # in tftp/
HEADER_FILE = "header_a_patched.bin"         # in tftp/

SLOT_A_ROOTFS_OFFSET = 0xa60000
SLOT_A_ROOTFS_SIZE   = 0x1620000
SLOT_A_HEADER_OFFSET = 0x2080000
SLOT_A_HEADER_SIZE   = 0x20000

LOAD_ADDR = 0x42000000

POST_BOOT_STREAM_SECS = 180


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true",
                    help="Print the U-Boot sequence, don't execute")
    args = ap.parse_args()

    # Verify files staged in tftp/
    tftp_dir = ZXIC / "tftp"
    rootfs_path = tftp_dir / ROOTFS_FILE
    header_path = tftp_dir / HEADER_FILE

    for p in (rootfs_path, header_path):
        if not p.exists():
            print(f"ERROR: missing {p}", file=sys.stderr)
            print(f"Run ./prepare_slot_a.sh first.", file=sys.stderr)
            sys.exit(2)

    rootfs_size = rootfs_path.stat().st_size
    header_size = header_path.stat().st_size
    if rootfs_size != SLOT_A_ROOTFS_SIZE:
        print(f"ERROR: {rootfs_path} size {rootfs_size} != "
              f"expected {SLOT_A_ROOTFS_SIZE}", file=sys.stderr)
        sys.exit(2)
    if header_size != SLOT_A_HEADER_SIZE:
        print(f"ERROR: {header_path} size {header_size} != "
              f"expected {SLOT_A_HEADER_SIZE}", file=sys.stderr)
        sys.exit(2)

    print(f"Files OK:")
    print(f"  {rootfs_path}  ({rootfs_size:,} bytes = 0x{rootfs_size:x})")
    print(f"  {header_path}  ({header_size:,} bytes = 0x{header_size:x})")

    # Build U-Boot command sequence.
    # _do_reset_then expects list of (cmd, wait_pattern_or_seconds) tuples.
    seq = uart._PREAMBLE + [
        # --- 1. Flash rootfs ---
        (f"tftp 0x{LOAD_ADDR:x} {ROOTFS_FILE}",
         (b"Bytes transferred", 240)),
        (f"md.l 0x{LOAD_ADDR:x} 1",
         (b"=>", 5)),
        (f"nand erase 0x{SLOT_A_ROOTFS_OFFSET:x} 0x{SLOT_A_ROOTFS_SIZE:x}",
         (b"=>", 120)),
        (f"nand write 0x{LOAD_ADDR:x} 0x{SLOT_A_ROOTFS_OFFSET:x} "
         f"0x{SLOT_A_ROOTFS_SIZE:x}",
         (b"=>", 180)),

        # --- 2. Flash header (IMMEDIATELY after rootfs, NO reboot between) ---
        (f"tftp 0x{LOAD_ADDR:x} {HEADER_FILE}",
         (b"Bytes transferred", 60)),
        (f"md.l 0x{LOAD_ADDR + 0x48:x} 1",
         (b"=>", 5)),
        (f"md.l 0x{LOAD_ADDR + 0xa4:x} 1",
         (b"=>", 5)),
        (f"nand erase 0x{SLOT_A_HEADER_OFFSET:x} 0x{SLOT_A_HEADER_SIZE:x}",
         (b"=>", 30)),
        (f"nand write 0x{LOAD_ADDR:x} 0x{SLOT_A_HEADER_OFFSET:x} "
         f"0x{SLOT_A_HEADER_SIZE:x}",
         (b"=>", 60)),

        # --- 3. Reboot + stream UART to observe slot A boot ---
        ("reset", POST_BOOT_STREAM_SECS),
    ]

    if args.dry_run:
        print("\n=== DRY-RUN — U-Boot command sequence ===")
        for cmd, wait in seq:
            print(f"  {cmd!r}")
        print("\nWould take roughly:")
        print(f"  ~{60 + POST_BOOT_STREAM_SECS}s end-to-end")
        return 0

    print()
    print("=" * 70)
    print("Starting flash sequence — DO NOT INTERRUPT")
    print("Each NAND erase/write is ~1-3 min; please wait silently.")
    print("=" * 70)
    print()

    return uart._do_reset_then(seq)


if __name__ == "__main__":
    sys.exit(main() or 0)
