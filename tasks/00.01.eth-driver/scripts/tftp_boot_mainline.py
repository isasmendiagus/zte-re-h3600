#!/usr/bin/env python3
"""TFTP-boot mainline kernel from U-Boot prompt — no NAND flash, no cspstart.

Thin wrapper around lib/uart.py:flash_image_to_ram(). The lib owns the
entire workflow (DTR → cspstart → setenv preamble → tftp → bootm →
kernel-marker wait) plus all retry / DTR-recovery semantics.

Mainline runs from RAM. Next power-cycle returns to whatever's on NAND.
The kernel image is tftp/zImage_dtb.uimg (already wrapped by build_slotA.py).
"""
import os
import sys

sys.path.insert(0, os.path.normpath(os.path.join(
    os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "lib")))

# Force TCP transport (the bridge). Set BEFORE importing open_port.
os.environ.setdefault("UART_TCP", "1")
from uart import open_port, flash_image_to_ram  # noqa: E402


def main():
    print(">>> Opening UART (via bridge)")
    ser = open_port()
    ok = flash_image_to_ram(
        ser,
        image_name="zImage_dtb.uimg",
        load_addr=0x42000000,
        kernel_ready_marker="REPL ready",
        kernel_ready_timeout=120,
        max_retries=3,
    )
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
