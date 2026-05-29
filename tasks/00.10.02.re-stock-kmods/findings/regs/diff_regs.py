#!/usr/bin/env python3
"""Diff two memdump outputs (`<addr> <value>` per line).

Categorizes differences:
- ONLY_IN_STOCK: register is non-zero in stock, zero (or differs) in mainline
- ONLY_IN_MAINLINE: vice-versa (we set something stock doesn't)
- DIFFERENT: both set but different values
- AGREE: both set the same (suppressed from output unless --verbose)

Usage: diff_regs.py stock.txt mainline.txt
"""
import sys
from pathlib import Path

def load(path):
    out = {}
    for line in Path(path).read_text().splitlines():
        line = line.strip()
        if not line or len(line) < 17:
            continue
        try:
            addr_s, val_s = line.split()
            out[int(addr_s, 16)] = int(val_s, 16)
        except ValueError:
            continue
    return out

def annotate(addr):
    """Best-effort label for an offset within our 0x921c0000 window."""
    off = addr - 0x921c0000
    if 0x000000 <= off < 0x1c0000:
        return f"NPP[+0x{off:06x}]"
    if 0x1c0000 <= off < 0x340000:
        return f"NPP[+0x{off:06x}]"
    if 0x180000 <= off < 0x340000:
        return f"TM[+0x{off - 0x180000:06x}]"
    if 0x340000 <= off < 0x380000:
        return f"PP[+0x{off - 0x340000:06x}]"
    return f"?[+0x{off:06x}]"

def main():
    if len(sys.argv) != 3:
        sys.exit("usage: diff_regs.py stock.txt mainline.txt")
    stock = load(sys.argv[1])
    main_ = load(sys.argv[2])

    only_stock = []
    only_main = []
    diff = []
    for addr, sv in sorted(stock.items()):
        mv = main_.get(addr, 0)
        if sv == mv:
            continue
        if sv != 0 and mv == 0:
            only_stock.append((addr, sv, mv))
        elif sv == 0 and mv != 0:
            only_main.append((addr, sv, mv))
        else:
            diff.append((addr, sv, mv))
    # registers only in mainline (not in stock dump)
    for addr, mv in sorted(main_.items()):
        if addr in stock:
            continue
        if mv != 0:
            only_main.append((addr, 0, mv))

    print(f"=== Summary ===")
    print(f"ONLY_IN_STOCK : {len(only_stock):>6}   (stock sets, mainline doesn't)")
    print(f"DIFFERENT     : {len(diff):>6}   (both set, different values)")
    print(f"ONLY_IN_MAIN  : {len(only_main):>6}   (we set, stock doesn't)")
    print()

    print("=== ONLY_IN_STOCK (likely missing config) ===")
    for addr, sv, mv in only_stock:
        print(f"  {addr:08x}  stock={sv:08x}  mainline={mv:08x}  {annotate(addr)}")

    print()
    print("=== DIFFERENT values ===")
    for addr, sv, mv in diff:
        print(f"  {addr:08x}  stock={sv:08x}  mainline={mv:08x}  {annotate(addr)}")

    print()
    print("=== ONLY_IN_MAINLINE (we set, stock doesn't — sus) ===")
    for addr, sv, mv in only_main:
        print(f"  {addr:08x}  stock={sv:08x}  mainline={mv:08x}  {annotate(addr)}")

if __name__ == "__main__":
    main()
