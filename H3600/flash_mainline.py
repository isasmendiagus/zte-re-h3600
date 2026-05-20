#!/usr/bin/env python3
"""Auto-flash mainline kernel + modified header A from U-Boot via TFTP.

Workflow:
1. Wait for U-Boot prompt (user power-cycles)
2. Set network env (ipaddr=192.168.1.1, serverip=192.168.1.50)
3. tftp slotA.bin -> nand erase + write at 0x700000 (25 MiB area)
4. tftp header_A_modified.bin -> nand erase + write at 0x2080000 (1 block)
5. Clean autorun env, saveenv, reset
6. Stay logging — see if mainline boots automatically
"""
import sys, os, time
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from uart import open_port, send_slow, log_loop, _wait_for_boot_and_drive_prompts, LOG
import threading

PORT_IP = "192.168.1.1"
SERVER_IP = "192.168.1.50"

CMDS = [
    # cmd                                                     wait_after_seconds
    (f"setenv ipaddr {PORT_IP}",                              2),
    (f"setenv serverip {SERVER_IP}",                          2),
    # 1. Mainline kernel
    ("tftp 0x42000000 slotA.bin",                             45),  # ~11 MiB over 100Mbps
    ("nand erase 0x700000 0x1980000",                         15),
    ("nand write 0x42000000 0x700000 0xb00000",               60),  # ~11 MiB write
    # 2. Modified header
    ("tftp 0x42000000 header_A_modified.bin",                 8),
    ("nand erase 0x2080000 0x20000",                          5),
    ("nand write 0x42000000 0x2080000 0x20000",               8),
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
