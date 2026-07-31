#!/usr/bin/env python3
"""Diff the SIPC block (npp+0xc000 = phys 0x921cc000..0x921cc07c) live on
mainline against the stored STOCK capture.

WHY: the cold-start tracer (wedge_coldstart.py) localized wedge #2 to
0x921cc008 — three 4-bit gauges that climb in lockstep with HW-forwarded
traffic (ddd -> eee -> fff) and halt the fabric the moment they saturate at
0xf, then wrap to 0x111 and briefly recover. Stock reads 0x00000399 there
(high nibbles ZERO, i.e. they drain), so this is a genuine stock-vs-mainline
divergence and the most concrete wedge mechanism found so far. This tool
diffs the whole surrounding block to find the CONFIG register that makes
stock drain where mainline accumulates — the same shape as the already-fixed
RED_CFG bit6 "charge accounting never refunded" bug.

Reads via the debugfs poke PEEK idiom (paced), NOT a bulk memdump of the
0x92000000 region.

Usage: sipc_diff.py [label]
"""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ab_ctrs  # noqa: E402

STOCK_FILE = (Path(__file__).resolve().parent.parent /
              "tasks/00.01.eth-driver/captures/fpga/npp_block_stock.txt")
BASE = 0x921CC000
N = 32  # 0x00..0x7c


def load_stock():
    vals = {}
    if not STOCK_FILE.exists():
        return vals
    for line in STOCK_FILE.read_text().splitlines():
        m = re.match(r"^([0-9a-f]{8})\s+([0-9a-f]{8})\s*$", line.strip(), re.I)
        if m:
            vals[int(m.group(1), 16)] = int(m.group(2), 16)
    return vals


def read_live():
    addrs = [BASE + i * 4 for i in range(N)]
    vals = {}
    # chunk so the console never floods
    for i in range(0, len(addrs), 8):
        chunk = addrs[i:i + 8]
        cmds = ["echo %08x > /sys/kernel/debug/zx_eth/poke" % a for a in chunk]
        cmds.append("dmesg | busybox grep -a 'peek 0x' | busybox tail -%d"
                    % (len(chunk) + 3))
        out = ab_ctrs.zc(cmds, wait=2.0, hardcap=40)
        for a in chunk:
            m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % a, out, re.I)
            vals[a] = int(m[-1], 16) if m else None
    return vals


def main():
    label = sys.argv[1] if len(sys.argv) > 1 else "live"
    stock = load_stock()
    live = read_live()
    print("=== SIPC block 0x921cc000..0x%08x — mainline(%s) vs stock ===\n"
          % (BASE + (N - 1) * 4, label))
    print("%-10s %-12s %-12s %s" % ("addr", "mainline", "stock", "verdict"))
    diffs = []
    for i in range(N):
        a = BASE + i * 4
        lv, sv = live.get(a), stock.get(a)
        ls = "0x%08x" % lv if lv is not None else "??"
        ss = "0x%08x" % sv if sv is not None else "n/a"
        if lv is None or sv is None:
            verdict = ""
        elif lv == sv:
            verdict = "same"
        else:
            verdict = "**DIFF**"
            diffs.append((a, lv, sv))
        print("%-10s %-12s %-12s %s" % ("0x%08x" % a, ls, ss, verdict))
    print("\n=== %d differing registers ===" % len(diffs))
    for a, lv, sv in diffs:
        print("  0x%08x: mainline 0x%08x  stock 0x%08x  (xor 0x%08x)"
              % (a, lv, sv, lv ^ sv))


if __name__ == "__main__":
    main()
