#!/usr/bin/env python3
"""Flip the invert-DTR bit in the FT232R EEPROM, preserving everything else.

libftdi's decode/build is not perfectly symmetric for FT232R -- some bytes
past the string area get rewritten. We avoid that by:

  1. read EEPROM (chip -> internal buf, copy as `original`)
  2. eeprom_decode + eeprom_build  -- ONLY to make libftdi mark the context as
     'initialized_for_connected_device', so write_eeprom will accept the buf.
     We discard the rebuilt bytes.
  3. hand-craft the new buf: original with byte 0x0B's DTR bit flipped + a
     recomputed FT232R checksum stored at words 63.
  4. set_eeprom_buf to push our crafted bytes into the now-initialized context.
  5. write_eeprom.

Sanity checks bail before the write if our checksum of the unmodified original
doesn't match what was stored there (i.e. our checksum algorithm is wrong).
"""
import ctypes
import ctypes.util
import os
import sys

VID, PID = 0x0403, 0x6001

EEPROM_SIZE = 128
INVERT_BYTE_OFFSET = 0x0B
INVERT_DTR_BIT = 1 << 4
CHECKSUM_OFFSETS = (0x7E, 0x7F)

# libftdi enum ftdi_eeprom_value (stable across 1.x): INVERT = 30
EEPROM_INVERT = 30

lib = ctypes.CDLL(ctypes.util.find_library('ftdi1') or 'libftdi1.so.2')

lib.ftdi_new.restype = ctypes.c_void_p
lib.ftdi_free.argtypes = [ctypes.c_void_p]
lib.ftdi_usb_open.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
lib.ftdi_usb_open.restype = ctypes.c_int
lib.ftdi_usb_close.argtypes = [ctypes.c_void_p]
lib.ftdi_usb_close.restype = ctypes.c_int
lib.ftdi_read_eeprom.argtypes = [ctypes.c_void_p]
lib.ftdi_read_eeprom.restype = ctypes.c_int
lib.ftdi_write_eeprom.argtypes = [ctypes.c_void_p]
lib.ftdi_write_eeprom.restype = ctypes.c_int
lib.ftdi_get_eeprom_buf.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int]
lib.ftdi_get_eeprom_buf.restype = ctypes.c_int

lib.ftdi_set_eeprom_buf.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int]
lib.ftdi_set_eeprom_buf.restype = ctypes.c_int
lib.ftdi_eeprom_decode.argtypes = [ctypes.c_void_p, ctypes.c_int]
lib.ftdi_eeprom_decode.restype = ctypes.c_int
lib.ftdi_eeprom_build.argtypes = [ctypes.c_void_p]
lib.ftdi_eeprom_build.restype = ctypes.c_int
lib.ftdi_get_eeprom_value.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
lib.ftdi_get_eeprom_value.restype = ctypes.c_int
lib.ftdi_set_eeprom_value.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
lib.ftdi_set_eeprom_value.restype = ctypes.c_int
lib.ftdi_get_error_string.argtypes = [ctypes.c_void_p]
lib.ftdi_get_error_string.restype = ctypes.c_char_p

lib.ftdi_erase_eeprom.argtypes = [ctypes.c_void_p]
lib.ftdi_erase_eeprom.restype = ctypes.c_int

lib.ftdi_write_eeprom_location.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_ushort]
lib.ftdi_write_eeprom_location.restype = ctypes.c_int

lib.ftdi_read_eeprom_location.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.POINTER(ctypes.c_ushort)]
lib.ftdi_read_eeprom_location.restype = ctypes.c_int


def die(ctx, msg):
    err = lib.ftdi_get_error_string(ctx).decode() if ctx else ''
    print(f"ERROR: {msg}: {err}", file=sys.stderr)
    sys.exit(1)


def get_buf(ctx):
    buf = ctypes.create_string_buffer(EEPROM_SIZE)
    if lib.ftdi_get_eeprom_buf(ctx, buf, EEPROM_SIZE) < 0:
        die(ctx, "get_eeprom_buf")
    return bytearray(buf.raw)


def diff_bytes(a, b):
    return [(i, a[i], b[i]) for i in range(len(a)) if a[i] != b[i]]


def rotl16(v, n):
    return ((v << n) | (v >> (16 - n))) & 0xFFFF


def ft232r_checksum(buf):
    """Checksum over words 0..62 (offsets 0x00..0x7D). Stored at word 63."""
    csum = 0xAAAA
    for i in range(0, 0x7E, 2):
        word = buf[i] | (buf[i + 1] << 8)
        csum = rotl16(csum ^ word, 1)
    return csum


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
        # 1) read EEPROM and grab a pristine copy of every byte
        if lib.ftdi_read_eeprom(ctx) < 0:
            die(ctx, "read_eeprom")
        original = get_buf(ctx)
        print(f"read EEPROM ok ({EEPROM_SIZE} bytes)")

        orig_invert = original[INVERT_BYTE_OFFSET]
        orig_csum = original[0x7E] | (original[0x7F] << 8)
        print(f"current invert byte (0x0B) = 0x{orig_invert:02x}")
        print(f"current checksum word      = 0x{orig_csum:04x}")

        # sanity check: our checksum algorithm reproduces the stored one
        verify = ft232r_checksum(original)
        if verify != orig_csum:
            print(f"ERROR: my checksum algo gave 0x{verify:04x}, EEPROM has 0x{orig_csum:04x}.")
            print("       The byte order or algorithm is wrong for this chip. Aborting.")
            sys.exit(2)
        print(f"checksum algo verified (0x{verify:04x} matches)")

        # 2) decode + build only to flip libftdi's 'initialized_for_connected_device' flag
        if lib.ftdi_eeprom_decode(ctx, 0) < 0:
            die(ctx, "eeprom_decode")
        if lib.ftdi_eeprom_build(ctx) < 0:
            die(ctx, "eeprom_build")

        # 3) craft new buf = original with only invert bit + checksum changed
        new_buf = bytearray(original)
        if desired_bit_on:
            new_buf[INVERT_BYTE_OFFSET] |= INVERT_DTR_BIT
        else:
            new_buf[INVERT_BYTE_OFFSET] &= ~INVERT_DTR_BIT
        if new_buf[INVERT_BYTE_OFFSET] == orig_invert:
            print("nothing to do: invert bit already in target state")
            return
        new_csum = ft232r_checksum(new_buf)
        new_buf[0x7E] = new_csum & 0xFF
        new_buf[0x7F] = (new_csum >> 8) & 0xFF
        print(f"new invert byte            = 0x{new_buf[INVERT_BYTE_OFFSET]:02x}")
        print(f"new checksum word          = 0x{new_csum:04x}")

        diffs = diff_bytes(original, new_buf)
        allowed = {INVERT_BYTE_OFFSET, *CHECKSUM_OFFSETS}
        unexpected = [d for d in diffs if d[0] not in allowed]
        if unexpected:
            print(f"BUG: crafted buf has unexpected diffs: {unexpected}", file=sys.stderr)
            sys.exit(3)
        print("\nbytes to write that differ from current EEPROM:")
        for off, a, b in diffs:
            print(f"  0x{off:02x}: 0x{a:02x} -> 0x{b:02x}")

        # 4) push our crafted bytes back into the (now initialized) libftdi context
        if lib.ftdi_set_eeprom_buf(ctx, ctypes.c_char_p(bytes(new_buf)), EEPROM_SIZE) < 0:
            die(ctx, "set_eeprom_buf")

        if not os.environ.get('FT232_CONFIRM_WRITE'):
            print("\nDRY RUN. Re-run with FT232_CONFIRM_WRITE=1 to flash.")
            return

        # 4b) sanity: confirm the buf we're about to write actually contains our bytes
        pre_write = get_buf(ctx)
        if pre_write != new_buf:
            unmatched = diff_bytes(pre_write, new_buf)
            print(f"INTERNAL ERROR: libftdi's buf doesn't match what I set; diffs: {unmatched}")
            sys.exit(4)
        print("\nlibftdi internal buf matches crafted buf (set_eeprom_buf worked)")

        # 5) erase + write to chip
        print("erasing EEPROM...")
        rc = lib.ftdi_erase_eeprom(ctx)
        print(f"  erase_eeprom rc={rc}")
        if rc < 0:
            die(ctx, "erase_eeprom")

        # set_eeprom_buf again because erase may have cleared the internal buf
        if lib.ftdi_set_eeprom_buf(ctx, ctypes.c_char_p(bytes(new_buf)), EEPROM_SIZE) < 0:
            die(ctx, "set_eeprom_buf (post-erase)")

        print("writing EEPROM...")
        rc = lib.ftdi_write_eeprom(ctx)
        print(f"  write_eeprom rc={rc}")
        if rc < 0:
            die(ctx, "write_eeprom")

        # 6) read back from chip and verify byte-by-byte
        print("\nreading back to verify...")
        if lib.ftdi_read_eeprom(ctx) < 0:
            die(ctx, "read_eeprom (verify)")
        readback = get_buf(ctx)
        ver_diffs = diff_bytes(new_buf, readback)
        if ver_diffs:
            print("VERIFY FAILED -- chip did not accept the write. Differences vs intended:")
            for off, want, got in ver_diffs[:20]:
                print(f"  0x{off:02x}: wrote 0x{want:02x}, read 0x{got:02x}")
            print("\nLikely causes:")
            print("  - FT232R clone with read-only EEPROM (common with fake chips)")
            print("  - EEPROM locked by a 'protect' bit (FT_PROG can sometimes lock these)")
            print("  - libftdi/kernel driver conflict (try detaching ftdi_sio first)")
            sys.exit(5)
        print(f"VERIFY OK -- all {EEPROM_SIZE} bytes match. UNPLUG + REPLUG to take effect.")
    finally:
        lib.ftdi_usb_close(ctx)
        lib.ftdi_free(ctx)


if __name__ == '__main__':
    main()
