#!/usr/bin/env python3
"""Brute-force the csp_crc algorithm.
Known data points (data, expected_crc):
  - stock kernel slot A: NAND[0x700000:0x35fdcc] -> 0x2fedcd6d
  - stock rootfs A:      NAND[0xa60000:0x1620000] -> 0xcad40158
  - 0xff-erased 22 MiB:                            -> 0x681487c5
The 1st returned value is the bitwise complement (XOR=ffffffff).
"""
import struct, time

NAND = open('/home/ubuntu/Projects/MYSELF/ZTE/H3600/h3600_nand_full.bin','rb').read()

# 4 known (data, expected) pairs
TESTS = [
    ('kernel_stock',  NAND[0x700000:0x700000+0x35fdcc],  0x2fedcd6d),
    ('rootfs_stock',  NAND[0xa60000:0xa60000+0x1620000], 0xcad40158),
    ('garbage_22m',   b'\xff' * 0x1620000,               0x681487c5),
]

# Try many CRC32 variants efficiently using lookup tables
def crc32_calc(poly, init, refin, refout, xorout, data):
    """Generic CRC32 with table."""
    if refin:
        # reflected (LSB-first) — build reflected poly table
        rpoly = 0
        for i in range(32):
            if poly & (1 << i):
                rpoly |= 1 << (31-i)
        table = []
        for i in range(256):
            r = i
            for _ in range(8):
                r = (r >> 1) ^ rpoly if (r & 1) else (r >> 1)
            table.append(r)
        crc = init
        # if init not reflected, would need to reflect — but most reflected algos use init that's already symmetric
        for b in data:
            crc = table[(crc ^ b) & 0xff] ^ (crc >> 8)
        if refout:
            pass  # already reflected
        else:
            # need to reflect
            r = 0
            for i in range(32):
                if crc & (1 << i): r |= 1 << (31-i)
            crc = r
        return crc ^ xorout
    else:
        # forward (MSB-first)
        table = []
        for i in range(256):
            r = i << 24
            for _ in range(8):
                r = ((r << 1) ^ poly) & 0xFFFFFFFF if (r & 0x80000000) else ((r << 1) & 0xFFFFFFFF)
            table.append(r)
        crc = init
        for b in data:
            crc = (table[((crc >> 24) ^ b) & 0xff] ^ ((crc << 8) & 0xFFFFFFFF))
        if refout:
            r = 0
            for i in range(32):
                if crc & (1 << i): r |= 1 << (31-i)
            crc = r
        return crc ^ xorout

# Common CRC32 polynomials
POLYNOMIALS = [
    0x04C11DB7,  # IEEE/Ethernet/Standard
    0x1EDC6F41,  # Castagnoli (CRC-32C)
    0xA833982B,  # CRC-32D
    0x814141AB,  # CRC-32Q (aviation)
    0x000000AF,  # XFER
    0x82F63B78,  # iSCSI (alt notation of Castagnoli)
    0xEDB88320,  # already-reflected IEEE
]
INITS = [0x00000000, 0xFFFFFFFF, 0xCBF43926, 0x12345678]
XOROUTS = [0x00000000, 0xFFFFFFFF]

# Use small data first for fast iteration
test_data = TESTS[2][1][:8192]   # 8KB of 0xff
expected = None  # we don't have a small-data ground truth

# Better: directly try all combos against the small TESTS
print("Testing all CRC32 variants against rootfs garbage (22 MiB of 0xff)...")
print(f"target: {hex(TESTS[2][2])}")
print()
matches = []
total = 0
t0 = time.time()
for poly in POLYNOMIALS:
    for init in INITS:
        for xorout in XOROUTS:
            for refin in [True, False]:
                for refout in [True, False]:
                    total += 1
                    try:
                        c = crc32_calc(poly, init, refin, refout, xorout, TESTS[2][1])
                        if c == TESTS[2][2]:
                            matches.append((poly, init, refin, refout, xorout, c))
                            print(f"MATCH! poly={poly:#x} init={init:#x} refin={refin} refout={refout} xorout={xorout:#x}")
                    except Exception as e:
                        pass
print(f"\nTested {total} variants in {time.time()-t0:.0f}s, {len(matches)} matches")

# If we found candidates, verify against the other data points
if matches:
    print("\nVerifying against other data points:")
    for poly, init, refin, refout, xorout, _ in matches:
        ok = True
        for name, data, expected_v in TESTS:
            c = crc32_calc(poly, init, refin, refout, xorout, data)
            if c != expected_v:
                print(f"  {name}: got {c:#x} expected {expected_v:#x}  FAIL")
                ok = False
                break
        if ok:
            print(f"  ALL MATCH: poly={poly:#x} init={init:#x} refin={refin} refout={refout} xorout={xorout:#x}")
