#!/usr/bin/env python3
"""Diff two register dumps (4-byte aligned). Print all offsets where they differ.

Usage: diff_regs.py STOCK OURS [base_addr_hex]
"""
import sys, struct

def main():
    if len(sys.argv) < 3:
        print("usage: diff_regs.py STOCK OURS [base_hex]")
        return 2
    base = int(sys.argv[3], 16) if len(sys.argv) >= 4 else 0
    a = open(sys.argv[1], 'rb').read()
    b = open(sys.argv[2], 'rb').read()
    n = min(len(a), len(b)) // 4
    diffs = []
    for i in range(n):
        wa = struct.unpack('<I', a[i*4:i*4+4])[0]
        wb = struct.unpack('<I', b[i*4:i*4+4])[0]
        if wa != wb:
            diffs.append((i*4, wa, wb))
    print(f"# stock={len(a)}B ours={len(b)}B compared={n*4}B")
    print(f"# {len(diffs)} differing words")
    print("# off (abs)       stock      ours")
    # Group by region (256 bytes) for skimming
    region_summary = {}
    for off, wa, wb in diffs:
        r = off & ~0xff
        region_summary[r] = region_summary.get(r, 0) + 1
    print(f"# top 20 noisy 256-byte regions:")
    for r, c in sorted(region_summary.items(), key=lambda x: -x[1])[:20]:
        print(f"#   0x{base+r:08x}: {c} diffs")
    print()
    # Detail (truncate if huge)
    MAX = 500
    for off, wa, wb in diffs[:MAX]:
        print(f"  0x{base+off:08x}  0x{wa:08x}  0x{wb:08x}  ({wa^wb:08x})")
    if len(diffs) > MAX:
        print(f"  ... {len(diffs)-MAX} more")
    return 0

if __name__ == "__main__":
    sys.exit(main())
