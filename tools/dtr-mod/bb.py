#!/usr/bin/env python3
"""bb - put FT232 in bitbang mode with per-pin direction control.

Bitbang mode lets you choose, per data pin, whether it's an output
(driven by the host) or an input (high-Z).  Useful when you want to
electrically isolate certain lines (e.g. TXD/RXD from a powered-off
peripheral) while still controlling others (e.g. DTR for a relay).

Pin map for FT232R bitbang:
  D0 TXD   D1 RXD   D2 RTS   D3 CTS
  D4 DTR   D5 DSR   D6 DCD   D7 RI

Direction mask: bit=1 -> output, bit=0 -> input (high-Z).

USAGE
  bb.py uart                     leave bitbang -> back to normal UART
  bb.py mode <hex>               enter bitbang, set direction mask
                                   e.g. 0x10 = DTR output only, all else hi-Z
                                        0x14 = DTR + RTS outputs
                                        0x00 = everything hi-Z
  bb.py dtr low|high|toggle      set DTR pin (chip must already be in bitbang)
  bb.py rts low|high|toggle      same for RTS
  bb.py status                   read all 8 pin levels

EXAMPLES
  # isolate TXD/RXD from a powered-off modem, keep DTR controllable for relay
  bb.py mode 0x10
  bb.py dtr high                 # relay ON  (DTR pin HIGH)
  bb.py dtr low                  # relay OFF (DTR pin LOW)

  # done -- back to UART for normal modem chat
  bb.py uart
"""
import ctypes
import ctypes.util
import sys

VID, PID = 0x0403, 0x6001
BITMODE_RESET = 0x00
BITMODE_BITBANG = 0x01

PIN = {'txd': 0, 'rxd': 1, 'rts': 2, 'cts': 3,
       'dtr': 4, 'dsr': 5, 'dcd': 6, 'ri': 7}

lib = ctypes.CDLL(ctypes.util.find_library('ftdi1') or 'libftdi1.so.2')
lib.ftdi_new.restype = ctypes.c_void_p
lib.ftdi_free.argtypes = [ctypes.c_void_p]
lib.ftdi_usb_open.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
lib.ftdi_usb_open.restype = ctypes.c_int
lib.ftdi_usb_close.argtypes = [ctypes.c_void_p]
lib.ftdi_usb_close.restype = ctypes.c_int
lib.ftdi_set_bitmode.argtypes = [ctypes.c_void_p, ctypes.c_ubyte, ctypes.c_ubyte]
lib.ftdi_set_bitmode.restype = ctypes.c_int
lib.ftdi_read_pins.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_ubyte)]
lib.ftdi_read_pins.restype = ctypes.c_int
lib.ftdi_write_data.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int]
lib.ftdi_write_data.restype = ctypes.c_int
lib.ftdi_get_error_string.argtypes = [ctypes.c_void_p]
lib.ftdi_get_error_string.restype = ctypes.c_char_p


def die(ctx, msg):
    err = lib.ftdi_get_error_string(ctx).decode() if ctx else ''
    print(f"ERROR: {msg}: {err}", file=sys.stderr)
    sys.exit(1)


def open_dev():
    ctx = lib.ftdi_new()
    if not ctx:
        die(None, "ftdi_new")
    if lib.ftdi_usb_open(ctx, VID, PID) < 0:
        die(ctx, "usb_open")
    return ctx


def read_pins(ctx):
    v = ctypes.c_ubyte(0)
    if lib.ftdi_read_pins(ctx, ctypes.byref(v)) < 0:
        die(ctx, "read_pins")
    return v.value


def write_pins(ctx, value):
    buf = ctypes.c_char_p(bytes([value & 0xFF]))
    if lib.ftdi_write_data(ctx, buf, 1) < 0:
        die(ctx, "write_data")


def cmd_status(ctx):
    v = read_pins(ctx)
    print(f"pins = 0x{v:02x}  bin = {v:08b}")
    for name, b in PIN.items():
        print(f"  D{b} {name:3s} = {(v >> b) & 1}")


def cmd_mode(ctx, mask_str):
    mask = int(mask_str, 0)
    if lib.ftdi_set_bitmode(ctx, mask, BITMODE_BITBANG) < 0:
        die(ctx, f"set_bitmode(BITBANG, mask=0x{mask:02x})")
    print(f"bitbang mode set, direction=0x{mask:02x}  (bit=1 means output)")
    for name, b in PIN.items():
        kind = "OUT" if (mask >> b) & 1 else "in (hi-Z)"
        print(f"  D{b} {name:3s} = {kind}")
    # initialise outputs to HIGH so DTR/RTS match their UART idle state
    write_pins(ctx, mask)
    print(f"initial output value = 0x{mask:02x} (all outputs HIGH)")


def cmd_uart(ctx):
    if lib.ftdi_set_bitmode(ctx, 0, BITMODE_RESET) < 0:
        die(ctx, "set_bitmode(RESET)")
    print("UART mode restored (TXD driven, DTR/RTS via TIOCM)")


def cmd_pin(ctx, pin_name, level):
    if pin_name not in PIN:
        die(None, f"unknown pin {pin_name}")
    bit = PIN[pin_name]
    cur = read_pins(ctx)
    if level == 'toggle':
        new = cur ^ (1 << bit)
    elif level in ('low', '0', 'l'):
        new = cur & ~(1 << bit)
    elif level in ('high', '1', 'h'):
        new = cur | (1 << bit)
    else:
        die(None, f"unknown level {level}")
    write_pins(ctx, new)
    # echo
    after = read_pins(ctx)
    pin_val = (after >> bit) & 1
    print(f"{pin_name.upper()} -> {'HIGH' if pin_val else 'LOW'}  full byte=0x{after:02x}")


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    cmd = sys.argv[1]
    ctx = open_dev()
    try:
        if cmd == 'status':
            cmd_status(ctx)
        elif cmd == 'mode':
            if len(sys.argv) < 3:
                die(None, "mode needs a hex mask, e.g. 'bb.py mode 0x10'")
            cmd_mode(ctx, sys.argv[2])
        elif cmd == 'uart':
            cmd_uart(ctx)
        elif cmd in PIN:
            if len(sys.argv) < 3:
                die(None, f"{cmd} needs a level: low|high|toggle")
            cmd_pin(ctx, cmd, sys.argv[2].lower())
        else:
            die(None, f"unknown command {cmd!r}")
    finally:
        lib.ftdi_usb_close(ctx)
        lib.ftdi_free(ctx)


if __name__ == '__main__':
    main()
