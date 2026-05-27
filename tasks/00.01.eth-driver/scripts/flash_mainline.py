#!/usr/bin/env python3
"""Auto-flash mainline kernel + modified header A from U-Boot via TFTP.

NAND LAYOUT (touched by this script):
  0x00700000 — slot A kernel region (25 MiB available; we write ~11 MiB + 0xff pad)
  0x02080000 — slot A BootPara header (128 KiB; we rewrite to point at new kernel)
DO NOT TOUCH:
  0x00000000-0x000bffff — bootloader (BRICK risk)
  0x02700000+           — slot B (kernel/rootfs/header — our recovery fallback)
Full NAND map + flash invariants: see tasks/00.04.flash-tool/README.md.

Workflow:
1. DTR reset → wait for U-Boot prompt
2. Set network env (ipaddr=192.168.1.1, serverip=192.168.1.50)
3. tftp slotA.bin (padded to 0xb00000 with 0xff)  → nand erase + write @ 0x700000
4. tftp header_A_modified.bin                      → nand erase + write @ 0x2080000
5. Clean autorun env, saveenv, reset
6. Stay logging — see if mainline boots automatically

CRC INVARIANTS:
  header[0x34] = LE u32 kernel_size for CRC (we use 0xb00000 = exact pad size)
  header[0x3c] = LE u32 zlib.crc32(slotA.bin padded to 0xb00000)
  header[0xa4] = LE u32 zlib.crc32(header[0:0xa4])
  The csp_crc in U-Boot log prints (A, ~A) — store A (the un-complemented value).

PADDING RULE (we have hit this twice — do not make it three):
  Pad slotA.bin to 0xb00000 with 0xff BEFORE TFTP. Otherwise nand-write picks
  up trailing RAM garbage and CRC mismatches.
"""
import sys, os, time
# tasks/00.01.eth-driver/scripts/ → zxic/lib/ (parent.parent.parent + lib for uart.py)
sys.path.insert(0, os.path.normpath(os.path.join(
    os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "lib")))
from uart import open_port, _wait_for_boot_and_drive_prompts, run_uboot_seq

# CMDS sent AFTER run_uboot_seq's _PREAMBLE (which already does the empty-
# newline wake + setenv ipaddr/serverip + tftpblocksize=1468). With
# tftpblocksize=1468 TFTP throughput is ~1 MiB/s (8× faster than the 146
# KiB/s default), so the 11 MB kernel transfers in ~12s instead of ~75s.
# Waits are conservative bounds, not measurements.
CMDS = [
    # 1. Mainline kernel — slotA.bin is padded to 0xc00000 by build_slotA.py.
    ("tftp 0x42000000 slotA.bin",                             60),
    ("nand erase 0x700000 0x1980000",                         60),
    ("nand write 0x42000000 0x700000 0xc00000",               120), # ~11 MiB write
    # 2. Modified header
    ("tftp 0x42000000 header_A_modified.bin",                 15),
    ("nand erase 0x2080000 0x20000",                          10),
    ("nand write 0x42000000 0x2080000 0x20000",               15),
    # 3. Cleanup + reboot
    ('setenv autorun ""',                                     2),
    ("saveenv",                                               5),
    ("reset",                                                 2),
]

def main():
    print(">>> Waiting for U-Boot prompt (power-cycle the modem now)...")
    ser = open_port()
    if not _wait_for_boot_and_drive_prompts(ser):
        print("ERROR: did not reach U-Boot prompt")
        return 1

    print("\n>>> U-Boot reached. Running flash sequence via run_uboot_seq helper.\n")
    run_uboot_seq(ser, CMDS)

    print("\n>>> All commands sent. Modem is rebooting now.")
    print(">>> Watching boot output — Ctrl+C to stop.\n")
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        pass

if __name__ == "__main__":
    sys.exit(main() or 0)
