#!/usr/bin/env python3
"""Auto-flash mainline kernel + modified header A from U-Boot via TFTP.

NAND LAYOUT (touched by this script):
  0x00700000 — slot A kernel region (25 MiB available; we write ~11 MiB + 0xff pad)
  0x02080000 — slot A BootPara header (128 KiB; we rewrite to point at new kernel)
DO NOT TOUCH:
  0x00000000-0x000bffff — bootloader (BRICK risk)
  0x02700000+           — slot B (kernel/rootfs/header — our recovery fallback)
Full NAND map + flash invariants: see tasks/00.03.nand-flash/README.md.

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
from uart import open_port, send_slow, log_loop, _wait_for_boot_and_drive_prompts, LOG
import threading

PORT_IP = "192.168.1.1"
SERVER_IP = "192.168.1.50"

CMDS = [
    # cmd                                                     wait_after_seconds
    (f"setenv ipaddr {PORT_IP}",                              2),
    (f"setenv serverip {SERVER_IP}",                          2),
    # 1. Mainline kernel.
    # 2026-05-22 BUG FIX: TFTP at ~150 KB/s for 11 MiB takes ~75s. The
    # previous 45s wait caused `nand erase`/`nand write` to be sent into
    # U-Boot mid-TFTP and silently dropped, so the kernel never got written.
    # Bumped to 180s to leave huge margin even if network is slow.
    ("tftp 0x42000000 slotA.bin",                             180),
    ("nand erase 0x700000 0x1980000",                         60),
    ("nand write 0x42000000 0x700000 0xb00000",               120), # ~11 MiB write
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

    print("\n>>> U-Boot reached. Streaming output to terminal + log...\n")
    fout = open(LOG, "ab")
    stop = threading.Event()
    t = threading.Thread(target=log_loop, args=(ser, fout, stop, True))
    t.start()
    time.sleep(1)

    for i, (cmd, wait) in enumerate(CMDS, 1):
        print(f"\n>>> [{i}/{len(CMDS)}] {cmd}  (wait {wait}s)")
        send_slow(ser, cmd)
        time.sleep(wait)

    print("\n>>> All commands sent. Modem is rebooting now.")
    print(">>> Watching boot output — Ctrl+C to stop.\n")
    try:
        while True: time.sleep(1)
    except KeyboardInterrupt:
        pass
    stop.set()
    t.join()
    fout.close()

if __name__ == "__main__":
    sys.exit(main() or 0)
