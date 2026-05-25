#!/usr/bin/env python3
"""TFTP-boot mainline kernel from U-Boot prompt — no NAND flash, no cspstart.

Always goes through the uart-bridge daemon (port 9999 data, 9998 ctl) so that
other processes can tail UART concurrently. The reset is an atomic DTR_PULSE
on the bridge's control port — reliable single-command, no client-side timing.

Each run:
  1. Atomic DTR_PULSE via bridge ctl port (300ms power-cycle)
  2. Wait for U-Boot prompt (autopilot enters boot mode + password)
  3. setenv ipaddr/serverip
  4. tftp 0x42000000 zImage_dtb.uimg — wait for "Bytes transferred" in log,
     NOT a fixed sleep (TFTP rate varies; old script's 120s could be too short
     OR send bootm into a half-finished tftp).
  5. bootm 0x42000000

Mainline runs from RAM. Next power-cycle returns to whatever's on NAND.
The kernel image is tftp/zImage_dtb.uimg (already wrapped by build_slotA.py).
"""
import os
import socket
import sys
import threading
import time

sys.path.insert(0, os.path.normpath(os.path.join(
    os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "lib")))
from uart import send_slow, log_loop, LOG  # noqa: E402

# Force TCP transport (the bridge). Set BEFORE importing open_port so the
# UART_TCP env-var check sees it.
os.environ.setdefault("UART_TCP", "1")
from uart import open_port  # noqa: E402

PORT_IP = "192.168.1.1"
SERVER_IP = "192.168.1.50"
KERNEL_IMG = "zImage_dtb.uimg"

CTL_HOST = os.environ.get("UART_TCP_HOST", "localhost")
CTL_PORT = int(os.environ.get("UART_TCP_CTL_PORT", "9998"))
BRIDGE_LOG = "/tmp/uart_bridge.log"


DTR_HOLD_SECS = 2.0  # bridge's DTR_PULSE is only 300ms — too short to fully
                     # discharge the device; we observed kernel surviving the
                     # blip and the OLD image kept running. lib/uart.py used
                     # 2.0s for the same reason — match it here.


def atomic_dtr_pulse():
    """Power-cycle via the bridge's control port (one greeting recv, then
    DTR_HIGH → sleep DTR_HOLD_SECS → DTR_LOW). Each setDTR is a single
    round-trip on the ctl socket, so the only host-side timing is the
    sleep between them — no per-byte send_slow race like the original
    ser.dtr=True/sleep/ser.dtr=False through the TCP wrapper. The
    bridge's bundled DTR_PULSE command is too short (300ms) for a clean
    reset on this device."""
    s = socket.create_connection((CTL_HOST, CTL_PORT), timeout=5)
    try:
        s.recv(1024)  # greeting "# uart_bridge ctl. commands: ..."
        s.sendall(b"DTR_HIGH\n")  # device OFF
        s.recv(1024)
        print(f"[reset] DTR HIGH (modem off) for {DTR_HOLD_SECS}s...")
        time.sleep(DTR_HOLD_SECS)
        s.sendall(b"DTR_LOW\n")   # device ON (boot)
        resp = s.recv(1024)
        print(f"[reset] DTR LOW → {resp.decode(errors='replace').strip()}")
    finally:
        s.close()


def wait_for_marker(log_path: str, marker: str, timeout: float,
                    start_offset: int = 0) -> bool:
    """Poll the bridge log for a substring. Returns True if found."""
    deadline = time.time() + timeout
    while time.time() < deadline:
        try:
            with open(log_path, "rb") as f:
                f.seek(start_offset)
                if marker.encode() in f.read():
                    return True
        except FileNotFoundError:
            pass
        time.sleep(0.5)
    return False


def main():
    print(">>> Atomic DTR_PULSE via bridge ctl port")
    try:
        atomic_dtr_pulse()
    except Exception as e:
        print(f"ERROR: bridge DTR_PULSE failed: {e}")
        print("  Is the uart-bridge daemon running? See tasks/00.04.02.uart-bridge/")
        return 1

    print(">>> Opening UART (via bridge)")
    ser = open_port()

    # Drive the cspstart prompts: 1, password, then U-Boot.
    print(">>> Waiting for cspstart prompts...")
    deadline = time.time() + 60
    buf = b""
    sent_one = sent_pw = False
    saw_uboot = False
    while time.time() < deadline:
        data = ser.read(512)
        if data:
            sys.stdout.buffer.write(data)
            sys.stdout.buffer.flush()
            buf += data
            if not sent_one and b"Press 1" in buf:
                ser.write(b"1\r")
                ser.flush()
                sent_one = True
                print("\n[autopilot] sent '1'")
            if sent_one and not sent_pw and b"password" in buf:
                ser.write(b"Boot4128s!\r")
                ser.flush()
                sent_pw = True
                print("\n[autopilot] sent password")
            if b"=>" in buf:
                saw_uboot = True
                break
        else:
            time.sleep(0.05)
    if not saw_uboot:
        print("ERROR: never reached U-Boot prompt")
        return 1

    print("\n>>> U-Boot reached. setenv + TFTP + bootm.")
    log_size_at_uboot = os.path.getsize(BRIDGE_LOG) if os.path.exists(BRIDGE_LOG) else 0

    fout = open(LOG, "ab")
    stop = threading.Event()
    t = threading.Thread(target=log_loop, args=(ser, fout, stop, True))
    t.start()
    time.sleep(0.5)

    send_slow(ser, f"setenv ipaddr {PORT_IP}"); time.sleep(1)
    send_slow(ser, f"setenv serverip {SERVER_IP}"); time.sleep(1)
    send_slow(ser, f"tftp 0x42000000 {KERNEL_IMG}")

    # Wait for "Bytes transferred" — adapts to TFTP speed.
    print(">>> Waiting for TFTP to complete...")
    if not wait_for_marker(BRIDGE_LOG, "Bytes transferred", timeout=300,
                           start_offset=log_size_at_uboot):
        print("ERROR: TFTP did not complete in 180s")
        stop.set(); t.join(); fout.close()
        return 1
    print(">>> TFTP done")

    time.sleep(1)
    send_slow(ser, "bootm 0x42000000")
    print(">>> bootm sent — kernel should boot now.")

    # Watch for a few seconds then exit; caller polls UART for kernel-up marker.
    time.sleep(3)
    stop.set()
    t.join()
    fout.close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
