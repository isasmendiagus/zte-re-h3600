#!/usr/bin/env python3
"""TFTP-boot mainline kernel from U-Boot prompt — no NAND flash, no cspstart.

Use this when iterating on mainline kernel changes that you do NOT want to
persist to NAND. Each run:
  1. DTR power-cycle the device
  2. Wait for U-Boot prompt (autopilot enters boot mode + password)
  3. setenv ipaddr/serverip + tftp + bootm

Mainline runs from RAM. Next power-cycle returns to whatever's on NAND
(stock if slot A is invalid, else slot A's persisted mainline).

The kernel image is tftp/zImage_dtb.uimg (already wrapped by build_slotA.py).
"""
import sys, os, time, threading
sys.path.insert(0, os.path.normpath(os.path.join(
    os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "lib")))
from uart import open_port, send_slow, log_loop, _wait_for_boot_and_drive_prompts, LOG

PORT_IP = "192.168.1.1"
SERVER_IP = "192.168.1.50"

CMDS = [
    (f"setenv ipaddr {PORT_IP}",                 2),
    (f"setenv serverip {SERVER_IP}",             2),
    ("tftp 0x42000000 zImage_dtb.uimg",          120),  # 12 MiB at ~150 KB/s
    ("bootm 0x42000000",                         2),
]

def main():
    print(">>> DTR resetting, waiting for U-Boot prompt...")
    ser = open_port()
    if not _wait_for_boot_and_drive_prompts(ser):
        print("ERROR: did not reach U-Boot prompt")
        return 1

    print("\n>>> U-Boot reached. Sending TFTP+bootm commands...\n")
    fout = open(LOG, "ab")
    stop = threading.Event()
    t = threading.Thread(target=log_loop, args=(ser, fout, stop, True))
    t.start()
    time.sleep(1)

    for i, (cmd, wait) in enumerate(CMDS, 1):
        print(f"\n>>> [{i}/{len(CMDS)}] {cmd}  (wait {wait}s)")
        send_slow(ser, cmd)
        time.sleep(wait)

    print("\n>>> All commands sent. Watching boot — Ctrl+C to stop.\n")
    try:
        while True: time.sleep(1)
    except KeyboardInterrupt:
        pass
    stop.set()
    t.join()
    fout.close()

if __name__ == "__main__":
    sys.exit(main() or 0)
