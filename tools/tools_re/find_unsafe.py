#!/usr/bin/env python3
"""
Find stack-buffer overflow candidates in cspd ARM binary.

Heuristic: scan all calls to sprintf/strcpy/strcat/sscanf/memcpy where:
  - destination (r0 just before the call) is loaded as `sub rN, fp, #imm` (stack-local)
  - the function does NOT use snprintf/strncpy/strncat in that block
  - the function's stack frame is small (< 1024 bytes) — small buffer = easier to overflow
  - reports buffer offset, function size, and a snippet around the call

Optionally filter for functions that touch network/IPC (recvfrom, recvmsg, msgrcv).
"""
import re, sys, os
from collections import defaultdict

DIS = "/tmp/cspd.dis"

# 1. Parse function boundaries
RE_FUNC_HEAD = re.compile(r'^([0-9a-f]+) <([^>]+)>:\s*$')
RE_INSTR     = re.compile(r'^\s*([0-9a-f]+):\s+([0-9a-f]+)\s+(.*?)$')
RE_BL_PLT    = re.compile(r'\bbl\s+([0-9a-f]+)\s+<(\w+)@plt>')
RE_SUB_FP    = re.compile(r'\bsub\s+(r[0-9a-z]+),\s+fp,\s+#(\d+)')
RE_SUB_SP    = re.compile(r'\bsub\s+sp,\s+sp,\s+#(\d+)')
RE_MOV_R0    = re.compile(r'\bmov\s+r0,\s+(r[0-9a-z]+)')
RE_LDR_R0    = re.compile(r'\bldr\s+r0,')

UNSAFE = {"strcpy", "strcat", "sprintf", "sscanf"}
SAFE_HINT = {"strncpy", "strncat", "snprintf", "memcpy_s", "strlcpy", "strlcat", "strnlen"}
IPC_HINT = {"recvfrom", "recvmsg", "msgrcv", "read", "fread", "fgets", "recv"}

# Functions with these names get prioritized (RE seed)
FOCUS_NAME_HINTS = ("Set", "Add", "Update", "Insert", "Process", "Handle", "Recv", "Parse", "Conf")

def parse():
    funcs = []
    cur = None  # (start_addr, name, instructions [(addr_int, raw, asm)])
    with open(DIS) as f:
        for ln in f:
            m = RE_FUNC_HEAD.match(ln)
            if m:
                if cur:
                    funcs.append(cur)
                cur = (int(m.group(1), 16), m.group(2), [])
                continue
            m = RE_INSTR.match(ln)
            if m and cur is not None:
                cur[2].append((int(m.group(1), 16), m.group(2), m.group(3)))
    if cur:
        funcs.append(cur)
    return funcs

def scan_function(fstart, fname, instrs):
    """Returns list of (call_idx, callee, dst_offset_from_fp, fn_stack_alloc, snippet)"""
    findings = []
    # 1. Find function's stack allocation (first `sub sp, sp, #N`)
    stack_alloc = 0
    for _, _, asm in instrs[:15]:
        m = RE_SUB_SP.search(asm)
        if m:
            stack_alloc = int(m.group(1))
            break

    # 2. Track fp-relative buffer registers across instructions
    # Map: register -> last fp offset
    fp_reg = {}
    has_safe_alt = False
    has_ipc = False

    for i, (addr, raw, asm) in enumerate(instrs):
        # Track fp-relative loads
        m = RE_SUB_FP.search(asm)
        if m:
            fp_reg[m.group(1)] = int(m.group(2))
            continue

        # Track which register r0 was MOV'd from
        m = RE_MOV_R0.search(asm)
        if m:
            src_reg = m.group(1)
            if src_reg in fp_reg:
                fp_reg["r0"] = fp_reg[src_reg]
            continue

        # Loads to r0 not from fp = unknown source
        if RE_LDR_R0.search(asm) and "fp" not in asm:
            fp_reg.pop("r0", None)

        # Detect calls
        m = RE_BL_PLT.search(asm)
        if m:
            callee = m.group(2)
            if callee in IPC_HINT:
                has_ipc = True
            if callee in SAFE_HINT:
                has_safe_alt = True
            if callee in UNSAFE:
                # Check if r0 dst is fp-relative
                dst_off = fp_reg.get("r0")
                if dst_off is not None and dst_off > 0:
                    # snippet: 5 instrs before
                    snippet = instrs[max(0,i-5):i+1]
                    findings.append({
                        "call_addr": addr,
                        "callee": callee,
                        "dst_fp_off": dst_off,
                        "stack_alloc": stack_alloc,
                        "snippet": snippet,
                    })

    return findings, has_ipc, has_safe_alt

def main():
    print(f"Parsing {DIS}...", file=sys.stderr)
    funcs = parse()
    print(f"  {len(funcs)} functions", file=sys.stderr)

    all_findings = []
    for fstart, fname, instrs in funcs:
        if not instrs or "@plt" in fname:
            continue
        findings, has_ipc, has_safe = scan_function(fstart, fname, instrs)
        for f in findings:
            f["fn_name"] = fname
            f["fn_addr"] = fstart
            f["fn_size_instr"] = len(instrs)
            f["has_ipc"] = has_ipc
            f["has_safe_alt"] = has_safe
            all_findings.append(f)

    # Score: small buffer + small stack = high risk
    def risk(f):
        s = 0
        # Smaller buffer = higher risk
        if f["dst_fp_off"] < 64: s += 5
        elif f["dst_fp_off"] < 256: s += 3
        elif f["dst_fp_off"] < 512: s += 1
        # IPC presence in function = bonus
        if f["has_ipc"]: s += 4
        # No safer alternative used in same function = suspicious (forgot to use it)
        if not f["has_safe_alt"]: s += 1
        # sprintf/sscanf riskier than strcpy
        if f["callee"] in ("sprintf", "sscanf"): s += 1
        # Hot function name
        if any(h in f["fn_name"] for h in FOCUS_NAME_HINTS): s += 2
        return s

    all_findings.sort(key=risk, reverse=True)

    print(f"\n{'='*80}\nTop 30 unsafe call sites (by risk score)\n{'='*80}\n")
    for f in all_findings[:30]:
        print(f"[{risk(f):2d}] {f['fn_name']}@0x{f['fn_addr']:x}  "
              f"call:{f['callee']}@0x{f['call_addr']:x}  "
              f"dst:fp-{f['dst_fp_off']}  alloc:{f['stack_alloc']}B  "
              f"{'IPC ' if f['has_ipc'] else ''}{'SAFE' if f['has_safe_alt'] else ''}")

    print(f"\n{'='*80}\nFull breakdown for top 8\n{'='*80}\n")
    for f in all_findings[:8]:
        print(f"\n--- {f['fn_name']} @ 0x{f['fn_addr']:x} (risk={risk(f)}) ---")
        print(f"  call: {f['callee']} @ 0x{f['call_addr']:x}")
        print(f"  dst buffer: fp-{f['dst_fp_off']} (stack alloc {f['stack_alloc']}B)")
        print(f"  IPC nearby: {f['has_ipc']}  Safe alt seen: {f['has_safe_alt']}")
        print(f"  context:")
        for addr, raw, asm in f["snippet"]:
            print(f"    {addr:08x}: {asm}")

if __name__ == "__main__":
    main()
