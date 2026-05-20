#!/usr/bin/env python3
"""Verify NAND content matches expected slotA.bin after flash."""
import sys, os, time, threading
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from uart import open_port, send_slow, log_loop, _wait_for_boot_and_drive_prompts, LOG

# Read first 256 bytes of NAND at 0x700000 (start of slot A)
CMDS = [
    ("nand read 0x42000000 0x700000 0x100", 5),
    ("md.b 0x42000000 0x100", 3),
    # Also read end of our written area (at slotA_real_size = 0xae01e8)
    ("nand read 0x42000000 0x7ae0e0 0x100", 5),
    ("md.b 0x42000000 0x100", 3),
    # Read at end of our 0xb00000 write
    ("nand read 0x42000000 0x11ffe0 0x100", 5),
    ("md.b 0x42000000 0x100", 3),
]

def main():
    print(">>> Power-cycle modem now...")
    ser = open_port()
    if not _wait_for_boot_and_drive_prompts(ser):
        return 1
    fout = open(LOG, "ab"); stop = threading.Event()
    t = threading.Thread(target=log_loop, args=(ser, fout, stop, True))
    t.start(); time.sleep(1)
    for cmd, w in CMDS:
        print(f">>> {cmd}")
        send_slow(ser, cmd); time.sleep(w)
    time.sleep(2)
    stop.set(); t.join(); fout.close()

if __name__ == "__main__":
    sys.exit(main() or 0)
