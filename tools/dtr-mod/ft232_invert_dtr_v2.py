#!/usr/bin/env python3
"""Flip the invert-DTR bit in the FT232R EEPROM and VERIFY the write.

Uses ftdi_write_eeprom_location() to write the two changed 16-bit words
directly, then reads them back via ftdi_read_eeprom_location() to confirm
the bytes actually landed on the chip. No reliance on the libftdi
decode/build pipeline.

Words touched on FT232R EEPROM:
  word 5  (offset 0x0A-0x0B)  contains the invert-flags byte at 0x0B
  word 63 (offset 0x7E-0x7F)  checksum
"""
import ctypes
import ctypes.util
import os
import sys

VID, PID = 0x0403, 0x6001
EEPROM_SIZE = 128
INVERT_DTR_BIT = 1 << 4

lib = ctypes.CDLL(ctypes.util.find_library('ftdi1') or 'libftdi1.so.2')

lib.ftdi_new.restype = ctypes.c_void_p
lib.ftdi_free.argtypes = [ctypes.c_void_p]
lib.ftdi_usb_open.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
lib.ftdi_usb_open.restype = ctypes.c_int
lib.ftdi_usb_close.argtypes = [ctypes.c_void_p]
lib.ftdi_usb_close.restype = ctypes.c_int
lib.ftdi_read_eeprom.argtypes = [ctypes.c_void_p]
lib.ftdi_read_eeprom.restype = ctypes.c_int
lib.ftdi_get_eeprom_buf.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int]
lib.ftdi_get_eeprom_buf.restype = ctypes.c_int
lib.ftdi_write_eeprom_location.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_ushort]
lib.ftdi_write_eeprom_location.restype = ctypes.c_int
lib.ftdi_read_eeprom_location.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.POINTER(ctypes.c_ushort)]
lib.ftdi_read_eeprom_location.restype = ctypes.c_int
lib.ftdi_get_error_string.argtypes = [ctypes.c_void_p]
lib.ftdi_get_error_string.restype = ctypes.c_char_p


def die(ctx, msg):
    err = lib.ftdi_get_error_string(ctx).decode() if ctx else ''
    print(f"ERROR: {msg}: {err}", file=sys.stderr)
    sys.exit(1)


def rotl16(v, n):
    return ((v << n) | (v >> (16 - n))) & 0xFFFF


def checksum(words63):
    """FT232R: rotl16(csum ^ word, 1) starting from 0xAAAA over words 0..62."""
    c = 0xAAAA
    for w in words63:
        c = rotl16(c ^ w, 1)
    return c


def read_word(ctx, addr):
    v = ctypes.c_ushort(0)
    if lib.ftdi_read_eeprom_location(ctx, addr, ctypes.byref(v)) < 0:
        die(ctx, f"read_eeprom_location({addr})")
    return v.value


def dump_words(ctx):
    """Read full EEPROM as a list of 64 16-bit words."""
    if lib.ftdi_read_eeprom(ctx) < 0:
        die(ctx, "read_eeprom")
    buf = ctypes.create_string_buffer(EEPROM_SIZE)
    if lib.ftdi_get_eeprom_buf(ctx, buf, EEPROM_SIZE) < 0:
        die(ctx, "get_eeprom_buf")
    data = bytearray(buf.raw)
    return [data[i] | (data[i+1] << 8) for i in range(0, EEPROM_SIZE, 2)], data


def main():
    desired_bit_on = True
    if len(sys.argv) > 1 and sys.argv[1] in ('--off', '--clear'):
        desired_bit_on = False

    ctx = lib.ftdi_new()
    if not ctx:
        die(None, "ftdi_new failed")
    if lib.ftdi_usb_open(ctx, VID, PID) < 0:
        die(ctx, f"open {VID:04x}:{PID:04x}")

    try:
        words, raw = dump_words(ctx)
        orig_w5 = words[5]
        orig_w63 = words[63]
        orig_invert = (orig_w5 >> 8) & 0xFF
        print(f"current word 5  (offset 0x0A) = 0x{orig_w5:04x}  invert byte = 0x{orig_invert:02x}")
        print(f"current word 63 (checksum)   = 0x{orig_w63:04x}")

        # sanity: recompute checksum from current words[0..62] and compare
        calc = checksum(words[:63])
        if calc != orig_w63:
            print(f"ERROR: checksum mismatch on read: calc=0x{calc:04x} stored=0x{orig_w63:04x}")
            sys.exit(2)
        print(f"checksum algo verified (0x{calc:04x})")

        # compute new word 5 (flip invert DTR bit in the high byte)
        if desired_bit_on:
            new_invert = orig_invert | INVERT_DTR_BIT
        else:
            new_invert = orig_invert & ~INVERT_DTR_BIT
        if new_invert == orig_invert:
            print("nothing to do: invert bit already in target state")
            return

        new_w5 = (orig_w5 & 0x00FF) | (new_invert << 8)
        new_words = list(words)
        new_words[5] = new_w5
        new_w63 = checksum(new_words[:63])
        new_words[63] = new_w63

        print(f"\nwill write:")
        print(f"  word 5  : 0x{orig_w5:04x} -> 0x{new_w5:04x}   (invert byte 0x{orig_invert:02x} -> 0x{new_invert:02x})")
        print(f"  word 63 : 0x{orig_w63:04x} -> 0x{new_w63:04x}  (checksum)")

        if not os.environ.get('FT232_CONFIRM_WRITE'):
            print("\nDRY RUN. Re-run with FT232_CONFIRM_WRITE=1 to flash.")
            return

        # Write each changed word, then verify by reading it back
        for addr, new_val in ((5, new_w5), (63, new_w63)):
            rc = lib.ftdi_write_eeprom_location(ctx, addr, new_val)
            if rc < 0:
                die(ctx, f"write_eeprom_location(word {addr})")
            print(f"wrote word {addr} = 0x{new_val:04x} (rc={rc})")

        # verify
        print("\nverifying by re-reading each touched word:")
        all_ok = True
        for addr, expected in ((5, new_w5), (63, new_w63)):
            got = read_word(ctx, addr)
            ok = (got == expected)
            all_ok = all_ok and ok
            print(f"  word {addr}: read 0x{got:04x}, expected 0x{expected:04x}  {'OK' if ok else 'MISMATCH'}")

        if not all_ok:
            print("\nWRITE FAILED -- chip did not accept changes. EEPROM may be write-protected,")
            print("or this libftdi version's write_eeprom_location is broken for FT232R.")
            sys.exit(3)

        print("\nEEPROM verified. UNPLUG + REPLUG the adapter so the chip reloads it.")
    finally:
        lib.ftdi_usb_close(ctx)
        lib.ftdi_free(ctx)


if __name__ == '__main__':
    main()
