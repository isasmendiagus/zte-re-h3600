#!/usr/bin/env python3
"""Toggle DTR every N seconds while everything else is in high-Z.

Useful for verifying that bitbang mode actually drives the pin on a
suspicious / clone FT232: stick a multimeter (or LED) on DTR and watch it
oscillate between 0V and 3.3V every 1.5s.  TXD, RXD and the rest should be
floating (high-Z) the whole time.

Ctrl-C to stop.  On exit the chip is left in bitbang mode with DTR LOW;
run `tools/bb.py uart` afterwards to restore normal UART.
"""
import ctypes
import ctypes.util
import signal
import sys
import time

VID, PID = 0x0403, 0x6001
BITMODE_BITBANG = 0x01
DIRECTION = 0x10        # only D4=DTR is output; everything else is input/hi-Z
PERIOD_S = 1.5

lib = ctypes.CDLL(ctypes.util.find_library('ftdi1') or 'libftdi1.so.2')
lib.ftdi_new.restype = ctypes.c_void_p
lib.ftdi_free.argtypes = [ctypes.c_void_p]
lib.ftdi_usb_open.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
lib.ftdi_usb_open.restype = ctypes.c_int
lib.ftdi_usb_close.argtypes = [ctypes.c_void_p]
lib.ftdi_usb_close.restype = ctypes.c_int
lib.ftdi_set_bitmode.argtypes = [ctypes.c_void_p, ctypes.c_ubyte, ctypes.c_ubyte]
lib.ftdi_set_bitmode.restype = ctypes.c_int
lib.ftdi_write_data.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int]
lib.ftdi_write_data.restype = ctypes.c_int
lib.ftdi_get_error_string.argtypes = [ctypes.c_void_p]
lib.ftdi_get_error_string.restype = ctypes.c_char_p


def die(ctx, msg):
    err = lib.ftdi_get_error_string(ctx).decode() if ctx else ''
    print(f"ERROR: {msg}: {err}", file=sys.stderr)
    sys.exit(1)


def write_pins(ctx, value):
    buf = ctypes.c_char_p(bytes([value & 0xFF]))
    if lib.ftdi_write_data(ctx, buf, 1) < 0:
        die(ctx, "write_data")


def main():
    period = float(sys.argv[1]) if len(sys.argv) > 1 else PERIOD_S

    ctx = lib.ftdi_new()
    if not ctx:
        die(None, "ftdi_new")
    if lib.ftdi_usb_open(ctx, VID, PID) < 0:
        die(ctx, "usb_open")

    stop = False

    def handle(*_):
        nonlocal stop
        stop = True

    signal.signal(signal.SIGINT, handle)
    signal.signal(signal.SIGTERM, handle)

    try:
        if lib.ftdi_set_bitmode(ctx, DIRECTION, BITMODE_BITBANG) < 0:
            die(ctx, "set_bitmode")
        print(f"bitbang mode, direction=0x{DIRECTION:02x} (only DTR is output)")
        print(f"toggling DTR every {period}s.  TXD/RXD/RTS/CTS/DSR/DCD/RI are hi-Z.")
        print("Ctrl-C to stop.\n")

        level = 0  # start LOW so first transition is LOW->HIGH (visible)
        i = 0
        while not stop:
            byte = DIRECTION if level else 0x00  # bit4=1 -> DTR HIGH; bit4=0 -> DTR LOW
            write_pins(ctx, byte)
            i += 1
            print(f"  [{i:4d}] DTR={'HIGH' if level else 'LOW '}  (wrote 0x{byte:02x})", flush=True)
            # sleep in small steps so Ctrl-C is snappy
            t_end = time.monotonic() + period
            while not stop and time.monotonic() < t_end:
                time.sleep(0.05)
            level ^= 1
    finally:
        # leave with DTR LOW so the relay (if any) is in a known off state
        try:
            write_pins(ctx, 0x00)
        except SystemExit:
            pass
        lib.ftdi_usb_close(ctx)
        lib.ftdi_free(ctx)
        print("\nstopped.  chip is still in bitbang mode (DTR LOW).")
        print("run `tools/bb.py uart` to restore normal UART.")


if __name__ == '__main__':
    main()
