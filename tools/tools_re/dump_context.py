#!/usr/bin/env python3
"""Dump disasm context around target call sites + walk back to find bound checks."""
import re, sys

DIS = sys.argv[1] if len(sys.argv) > 1 else "/tmp/cspd.dis"

# Targets: (function_name, call_addr, label)
TARGETS = [
    ("fmMgrAsynMsg",      0x93c3c, "memcpy → global 0x24e74c (1st)"),
    ("fmMgrAsynMsg",      0x941c4, "memcpy → global 0x24e74c (2nd)"),
    ("_logConfigLogServer", 0xc3978, "memcpy → global 0x260e7c (1st)"),
    ("_logConfigLogServer", 0xc3bd0, "memcpy → global 0x260e7c (2nd)"),
    ("SrmMain",           0x2ae64, "memcpy → global 0x24c1c0"),
    ("SrmMain",           0x2ae74, "memcpy → global 0x24c1c8"),
    ("SrmMain",           0x2aea4, "memcpy → global 0x24c1d8"),
    ("TrafficRateGet",    0x8fa30, "sprintf → global 0x260d68 (1st)"),
    ("TrafficRateGet",    0x8fb20, "sprintf → global 0x260d68 (2nd)"),
]

# Parse disasm into per-function instruction lists
funcs = {}
fname = None; lst = []
with open(DIS) as f:
    for ln in f:
        m = re.match(r'^([0-9a-f]+) <([^>]+)>:', ln)
        if m:
            if fname: funcs[fname] = lst
            fname = m.group(2); lst = []
            continue
        lst.append(ln)
if fname: funcs[fname] = lst

def show(fn_name, target, before=18, after=4):
    if fn_name not in funcs:
        print(f"  [!] {fn_name} not in disasm"); return
    lines = funcs[fn_name]
    for i, ln in enumerate(lines):
        m = re.match(r'\s*([0-9a-f]+):', ln)
        if m and int(m.group(1),16) == target:
            for j in range(max(0,i-before), min(len(lines), i+after)):
                print(f"  {lines[j].rstrip()}")
            return
    print(f"  [!] addr 0x{target:x} not found in {fn_name}")

for fn, addr, label in TARGETS:
    print(f"\n{'='*80}\n{fn} @ 0x{addr:x} — {label}\n{'='*80}")
    show(fn, addr)
