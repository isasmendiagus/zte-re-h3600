#!/usr/bin/env python3
# Phase 6 Stage 2b — build the CLA hash key + ram2 entry for a v4 flow, compute
# candidate buckets offline (CRC-32C, validated == HW engine), for the slot-sweep test.
import sys

def _table(poly):
    t = []
    for i in range(256):
        c = i << 24
        for _ in range(8):
            c = ((c << 1) ^ poly) if (c & 0x80000000) else (c << 1)
            c &= 0xffffffff
        t.append(c)
    return t

_T = _table(0x1EDC6F41)  # CRC-32C, confirmed == HW hash engine on mainline


def crc45(buf):
    h = 0
    for x in bytes(buf)[::-1]:           # engine reverses the 45-byte key, then CRC
        h = (_T[(x ^ (h >> 24)) & 0xff] ^ ((h << 8) & 0xffffffff)) & 0xffffffff
    return h & 0xffff


def putbits(buf, start, nbits, val):
    for i in range(nbits):
        if (val >> i) & 1:
            buf[(start + i) // 8] |= 1 << ((start + i) % 8)


def ip_shorts(ip):
    o = [int(x) for x in ip.split('.')]
    return (o[0] << 8 | o[1], o[2] << 8 | o[3])


def extra_for(src, dst, sport, dport, proto):
    sa = ip_shorts(src); da = ip_shorts(dst)
    # extra_data0..6, byte-order derived by matching the captured stock template
    return [proto, sa[0], sa[1], da[0], da[1], sport, dport]


def build_key(outport, inport, extra):
    buf = bytearray(45)
    putbits(buf, 0, 5, outport & 0x1f)
    putbits(buf, 5, 12, inport & 0xfff)
    for n, d in enumerate(extra):
        putbits(buf, 33 + 16 * n, 16, d & 0xffff)
    return buf


def key_words(buf):
    w = []
    for i in range(12):
        v = 0
        for j in range(4):
            k = i * 4 + j
            if k < 45:
                v |= buf[k] << (8 * j)
        w.append(v)
    return w


# captured stock ram2 fwd entry template (15 words; tuple at byte offsets 0x13..0x20)
TEMPLATE = [0x03005044, 0xfa11c000, 0x00000608, 0x80000000, 0x06000009,
            0x32c0a800, 0x010a0901, 0x51ce4b09, 0x00000014, 0, 0, 0, 0, 0, 0]
TUPLE_OFFS = [0x13, 0x15, 0x17, 0x19, 0x1b, 0x1d, 0x1f]


def build_entry(extra):
    ent = bytearray(60)
    for i, w in enumerate(TEMPLATE):
        for j in range(4):
            ent[i * 4 + j] = (w >> (8 * j)) & 0xff
    for off, val in zip(TUPLE_OFFS, extra):
        ent[off] = val & 0xff
        ent[off + 1] = (val >> 8) & 0xff
    return [sum(ent[i * 4 + j] << (8 * j) for j in range(4)) for i in range(15)]


if __name__ == "__main__":
    src, dst = "192.168.9.50", "172.31.9.50"
    sport, dport, proto = 40000, 5201, 6
    extra = extra_for(src, dst, sport, dport, proto)
    print("flow %s:%d -> %s:%d proto %d" % (src, sport, dst, dport, proto))
    print("extra shorts:", [hex(x) for x in extra])
    print("--- raw hash + bucket per inport (outport=0) ---")
    for inport in (5, 4, 3, 2, 1, 0):
        raw = crc45(build_key(0, inport, extra))
        print("  inport=%d raw=0x%04x  &0xff=0x%02x  &0x1ff=0x%03x" %
              (inport, raw, raw & 0xff, raw & 0x1ff))
    print("--- verify key words (feed to debugfs hashcalc) for inport=5 ---")
    print("  KEY12:", " ".join("%x" % x for x in key_words(build_key(0, 5, extra))))
    print("--- ram2 entry (template + my tuple), 15 words ---")
    print("  ENTRY:", " ".join("%x" % w for w in build_entry(extra)))
