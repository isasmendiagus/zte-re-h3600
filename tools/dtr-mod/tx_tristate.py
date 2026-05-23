#!/usr/bin/env python3
"""Put the FT232 data pins (TXD/RXD/DTR/RTS/etc) into high-Z, or back to UART.

Two states:
  off      bitbang mode with direction=0x00 -> all pins are inputs / high-Z
  on       reset mode -> normal UART, TXD actively driven

NB: while 'off', /dev/ttyUSB0 will not behave as a UART -- the chip is in
bitbang mode.  Use this only when you want to electrically isolate the FT232
from a powered-off peripheral (avoiding back-powering through ESD diodes).
"""
import ctypes
import ctypes.util
import sys

VID, PID = 0x0403, 0x6001

BITMODE_RESET = 0x00
BITMODE_BITBANG = 0x01

lib = ctypes.CDLL(ctypes.util.find_library('ftdi1') or 'libftdi1.so.2')
lib.ftdi_new.restype = ctypes.c_void_p
lib.ftdi_free.argtypes = [ctypes.c_void_p]
lib.ftdi_usb_open.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
lib.ftdi_usb_open.restype = ctypes.c_int
lib.ftdi_usb_close.argtypes = [ctypes.c_void_p]
lib.ftdi_usb_close.restype = ctypes.c_int
lib.ftdi_set_bitmode.argtypes = [ctypes.c_void_p, ctypes.c_ubyte, ctypes.c_ubyte]
lib.ftdi_set_bitmode.restype = ctypes.c_int
lib.ftdi_get_error_string.argtypes = [ctypes.c_void_p]
lib.ftdi_get_error_string.restype = ctypes.c_char_p


def die(ctx, msg):
    err = lib.ftdi_get_error_string(ctx).decode() if ctx else ''
    print(f"ERROR: {msg}: {err}", file=sys.stderr)
    sys.exit(1)


def main():
    if len(sys.argv) != 2 or sys.argv[1] not in ('off', 'on', 'hiZ', 'uart'):
        print(f"usage: {sys.argv[0]} off|on    (off=tristate, on=UART)")
        sys.exit(1)
    tristate = sys.argv[1] in ('off', 'hiZ')

    ctx = lib.ftdi_new()
    if not ctx:
        die(None, "ftdi_new")
    if lib.ftdi_usb_open(ctx, VID, PID) < 0:
        die(ctx, "usb_open")
    try:
        if tristate:
            # mask 0x00 = all inputs (high-Z)
            if lib.ftdi_set_bitmode(ctx, 0x00, BITMODE_BITBANG) < 0:
                die(ctx, "set_bitmode(BITBANG, 0)")
            print("FT232 data pins -> tristate (bitbang mode, direction=0x00)")
            print("NOTE: /dev/ttyUSB0 is no longer a real UART until you run 'on'")
        else:
            if lib.ftdi_set_bitmode(ctx, 0x00, BITMODE_RESET) < 0:
                die(ctx, "set_bitmode(RESET)")
            print("FT232 -> UART mode (TXD actively driven)")
    finally:
        lib.ftdi_usb_close(ctx)
        lib.ftdi_free(ctx)


if __name__ == '__main__':
    main()
