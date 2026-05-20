#!/usr/bin/env python3
"""
Find unsafe writes to GLOBAL buffers in .data/.bss of an ELF (httpd or cspd).

Heuristic ARM ABI pattern:
    ldr rN, [pc, #X]    ; loads global addr from literal pool
    ... (passed as r0/r1/dst to strcpy/sprintf/memcpy/recv/strcat)
    bl strcpy@plt       ; etc.

If dst is in .data or .bss range AND no obvious size check before, flag it.
"""
import re, sys
from collections import defaultdict

DIS = sys.argv[1] if len(sys.argv) > 1 else "/tmp/httpd.dis"
print(f"Analyzing {DIS}", file=sys.stderr)

# Section ranges (httpd):
#   .data  124534-140cac  (file_offset .data) → virt 0x124534-0x140cac
#   .bss   1413f0-15392c  → virt 0x1413f0-0x15392c
# For cspd: needs different ranges
RANGES = {
    "httpd": [(0x124534, 0x140cac, ".data"), (0x1413f0, 0x15392c, ".bss")],
    "cspd":  [(0x213108, 0x215390, ".data.rel.ro"),
              (0x2188f0, 0x245ab8, ".data"),
              (0x2459d0, 0x300000, ".bss")],
}
RANGE_KEY = "httpd" if "httpd" in DIS else "cspd"

def in_global(addr):
    for lo, hi, name in RANGES[RANGE_KEY]:
        if lo <= addr < hi: return name
    return None

RE_FUNC_HEAD = re.compile(r'^([0-9a-f]+) <([^>]+)>:\s*$')
RE_LDR_PC    = re.compile(r'\s*([0-9a-f]+):\s+[0-9a-f]+\s+ldr\s+(r\d+),\s+\[pc,\s+#(\d+)\]')
RE_BL_PLT    = re.compile(r'\s*([0-9a-f]+):\s+[0-9a-f]+\s+bl\s+[0-9a-f]+\s+<(\w+)@plt>')
RE_MOV_REG   = re.compile(r'\s*[0-9a-f]+:\s+[0-9a-f]+\s+mov\s+(r\d+),\s+(r\d+)')
RE_STR_BYTE  = re.compile(r'\s*[0-9a-f]+:\s+[0-9a-f]+\s+strb?\s+r\d+,\s+\[(r\d+)')

UNSAFE = {"strcpy","strcat","sprintf","sscanf","memcpy","recv","read","fread","fgets"}

# Pre-load literal pool word values
literals = {}  # addr → value
RE_WORD = re.compile(r'\s*([0-9a-f]+):\s+([0-9a-f]+)\s+\.word')
with open(DIS) as f:
    for ln in f:
        m = RE_WORD.match(ln)
        if m: literals[int(m.group(1),16)] = int(m.group(2),16)
print(f"  literal pool entries: {len(literals)}", file=sys.stderr)

# Scan for unsafe-call sites with global dst
findings = []
fname = None
fnstart = 0
reg_state = {}    # reg -> global addr if known
calls_in_fn = []  # for current function (reset per function)

with open(DIS) as f:
    for ln in f:
        m = RE_FUNC_HEAD.match(ln)
        if m:
            fname = m.group(2); fnstart = int(m.group(1),16)
            reg_state = {}
            continue
        if fname is None or "@plt" in fname: continue

        m = RE_LDR_PC.match(ln)
        if m:
            instr_addr = int(m.group(1),16)
            reg = m.group(2)
            offset = int(m.group(3))
            lit_addr = instr_addr + 8 + offset
            val = literals.get(lit_addr)
            if val is not None:
                reg_state[reg] = val
            else:
                reg_state.pop(reg, None)
            continue

        m = RE_MOV_REG.match(ln)
        if m:
            dst, src = m.group(1), m.group(2)
            if src in reg_state: reg_state[dst] = reg_state[src]
            elif dst in reg_state: del reg_state[dst]
            continue

        m = RE_BL_PLT.match(ln)
        if m:
            instr_addr = int(m.group(1),16)
            callee = m.group(2)
            if callee in UNSAFE:
                # Check r0 (dst) is a global
                dst = reg_state.get("r0")
                if dst and in_global(dst):
                    findings.append({
                        "fn": fname, "fn_addr": fnstart,
                        "call_addr": instr_addr, "callee": callee,
                        "dst_addr": dst, "section": in_global(dst),
                    })
            # any call clobbers r0-r3
            for r in ("r0","r1","r2","r3"):
                reg_state.pop(r, None)
            continue

        # Reset on branch (rough invalidation)
        if re.search(r'\bb(eq|ne|cs|cc|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al)?\s+', ln):
            # don't reset, branches don't always clobber; skip
            pass

# Group by dst global
by_dst = defaultdict(list)
for f in findings:
    by_dst[f["dst_addr"]].append(f)

print(f"\nFound {len(findings)} unsafe calls with global dst, "
      f"into {len(by_dst)} distinct globals\n")

print("="*80)
print("Top global buffers receiving unsafe writes (sorted by # call sites)")
print("="*80)
for dst, calls in sorted(by_dst.items(), key=lambda x: -len(x[1])):
    sec = calls[0]["section"]
    distinct_fns = {c["fn"] for c in calls}
    print(f"\n0x{dst:08x} [{sec}] — {len(calls)} unsafe writes from {len(distinct_fns)} fns")
    for c in calls[:8]:
        print(f"  [{c['callee']:7s}] in {c['fn']}@0x{c['fn_addr']:x} call@0x{c['call_addr']:x}")
    if len(calls) > 8:
        print(f"  ...+{len(calls)-8} more")
