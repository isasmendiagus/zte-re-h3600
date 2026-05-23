#!/usr/bin/env python3
"""Flash only the modified header A (kernel already in place).

NAND LAYOUT (touched):
  0x02080000 — slot A BootPara header (128 KiB) — REWRITTEN
DO NOT TOUCH: 0x0..0xc0000 (boot), 0x02700000+ (slot B = recovery).
Full NAND map + flash invariants: see tasks/00.03.nand-flash/README.md.

Use when:
- You've already flashed kernel content to slot A and just need to update
  the header's kernel CRC (e.g. you bumped kernel_size after a recompile).
- You want to swap "boot-me-first" flags between slot A and slot B.

Prerequisite: zxic/tftp/header_A_modified.bin already built (see
tasks/00.01.eth-driver/scripts/build_slotA.py for canonical builder).
"""
import sys, os, time
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "lib"))
from uart import open_port, send_slow, log_loop, _wait_for_boot_and_drive_prompts, LOG
import threading

CMDS = [
    ("setenv ipaddr 192.168.1.1",                       2),
    ("setenv serverip 192.168.1.50",                    2),
    ("tftp 0x42000000 header_A_modified.bin",           8),
    ("nand erase 0x2080000 0x20000",                    5),
    ("nand write 0x42000000 0x2080000 0x20000",         8),
    ("reset",                                           2),
]

def main():
    print(">>> Power-cycle modem now...")
    ser = open_port()
    if not _wait_for_boot_and_drive_prompts(ser):
        return 1
    print("\n>>> U-Boot reached. Flashing header...\n")
    fout = open(LOG, "ab"); stop = threading.Event()
    t = threading.Thread(target=log_loop, args=(ser, fout, stop, True))
    t.start(); time.sleep(1)
    for cmd, w in CMDS:
        print(f">>> {cmd}")
        send_slow(ser, cmd); time.sleep(w)
    print("\n>>> Done. Watching boot...\n")
    try:
        while True: time.sleep(1)
    except KeyboardInterrupt: pass
    stop.set(); t.join(); fout.close()

if __name__ == "__main__":
    sys.exit(main() or 0)
