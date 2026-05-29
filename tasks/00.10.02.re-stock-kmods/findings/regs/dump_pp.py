#!/usr/bin/env python3
"""Capture several long streams of the PP region, anchor each on the host-MAC
signature, majority-vote per u32, then diff vs stock.  One stream covers
PP 0x8000..~0xea00 (phys 0x92388000..0x92396a00)."""
import live_read2 as L
import sys
from collections import Counter

MAC = bytes([0x00,0x59,0xe9,0x62,0xa3,0xc8])  # host MAC LE at phys 0x923880a8
MAC_PHYS = 0x923880a8

def capture(n=4, settle=16.0):
    streams = []  # list of (byte0_phys, buf)
    for i in range(n):
        buf = L.read_once(0x1c8000, settle=settle, max_bytes=70000)
        si = buf.find(MAC)
        if si < 0:
            print(f"  cap{i}: MAC not found len={len(buf)}", file=sys.stderr)
            continue
        byte0 = MAC_PHYS - si
        streams.append((byte0, buf))
        print(f"  cap{i}: len={len(buf)} MAC@{si} byte0={byte0:08x} end={byte0+len(buf):08x}", file=sys.stderr)
    return streams

def getval(streams, phys):
    """Majority u32 at phys across streams."""
    vals = []
    for byte0, buf in streams:
        bi = phys - byte0
        if 0 <= bi and bi+4 <= len(buf):
            vals.append(buf[bi] | (buf[bi+1]<<8) | (buf[bi+2]<<16) | (buf[bi+3]<<24))
    if not vals:
        return None, 0
    c = Counter(vals)
    val, freq = c.most_common(1)[0]
    return val, freq

if __name__ == '__main__':
    st = L.stock()
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 4
    lo = int(sys.argv[2],16) if len(sys.argv) > 2 else 0x92388000
    hi = int(sys.argv[3],16) if len(sys.argv) > 3 else 0x92396a00
    streams = capture(n)
    print(f"\n# captured {len(streams)} streams; diffing PP {lo:08x}..{hi:08x}\n")
    diffs = []
    for phys in range(lo, hi, 4):
        val, freq = getval(streams, phys)
        if val is None:
            continue
        # require agreement when we have >=3 streams
        if len(streams) >= 3 and freq < 2:
            continue
        sv = st.get(phys, 0)
        if val != sv:
            diffs.append((phys, sv, val, freq, len(streams)))
    print(f"# {len(diffs)} divergences\n")
    for phys, sv, val, freq, ns in diffs:
        print(f"{phys:08x}  stock={sv:08x}  main={val:08x}  agree={freq}/{ns}")
