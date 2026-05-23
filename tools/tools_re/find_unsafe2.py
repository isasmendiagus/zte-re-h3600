#!/usr/bin/env python3
"""
Refined scanner for cspd:
- Lists ALL unsafe call sites
- Filters for "*Set*" / "*Update*" / "*Add*" functions (most likely set-handlers)
- Cross-checks against known sweet spots: ddnsMain (0x27790), writeVsftpdCfgFile (0x925f8)
- Reports buffer size (computed properly) AND likely src lineage (whether r1/r2 came from a fp offset
  larger than dst — i.e. potentially copy from larger src to smaller dst)
"""
import re, sys
from collections import defaultdict

DIS = "/tmp/cspd.dis"

RE_FUNC_HEAD = re.compile(r'^([0-9a-f]+) <([^>]+)>:\s*$')
RE_INSTR     = re.compile(r'^\s*([0-9a-f]+):\s+([0-9a-f]+)\s+(.*?)$')
RE_BL_PLT    = re.compile(r'\bbl\s+([0-9a-f]+)\s+<(\w+)@plt>')
RE_BL        = re.compile(r'\bbl\s+([0-9a-f]+)\s+<([^>]+)>')
RE_SUB_FP    = re.compile(r'\bsub\s+(r[0-9a-z]+),\s+fp,\s+#(\d+)')
RE_SUB_SP    = re.compile(r'\bsub\s+sp,\s+sp,\s+#(\d+)')
RE_MOV_REG   = re.compile(r'\bmov\s+(r[0-9a-z]+),\s+(r[0-9a-z]+)')
RE_LDR_PC    = re.compile(r'\bldr\s+(r[0-9a-z]+),\s+\[pc,\s+#(\d+)\]')

UNSAFE = {"strcpy", "strcat", "sprintf", "sscanf"}
SAFE_HINT = {"strncpy", "strncat", "snprintf"}
IPC_HINT = {"recvfrom","recvmsg","msgrcv","read","fread","fgets","recv"}

def parse():
    funcs = []
    cur = None
    with open(DIS) as f:
        for ln in f:
            m = RE_FUNC_HEAD.match(ln)
            if m:
                if cur: funcs.append(cur)
                cur = (int(m.group(1), 16), m.group(2), [])
                continue
            m = RE_INSTR.match(ln)
            if m and cur is not None:
                cur[2].append((int(m.group(1), 16), m.group(2), m.group(3)))
    if cur: funcs.append(cur)
    return funcs

def fp_offsets_used(instrs):
    """Collect all unique fp offsets referenced — gives buffer count + max range."""
    offs = set()
    for _, _, asm in instrs:
        for m in RE_SUB_FP.finditer(asm):
            offs.add(int(m.group(2)))
        # also fp+N for upward access
    return sorted(offs)

def callees(instrs):
    cs = set()
    for _, _, asm in instrs:
        m = RE_BL_PLT.search(asm)
        if m: cs.add(m.group(2))
        m = RE_BL.search(asm)
        if m: cs.add(m.group(2))
    return cs

def scan_function(fstart, fname, instrs):
    findings = []
    stack_alloc = 0
    for _, _, asm in instrs[:20]:
        m = RE_SUB_SP.search(asm)
        if m:
            stack_alloc = int(m.group(1)); break

    # All fp offsets used as buffer pointers (sub r?, fp, #N)
    fp_buffers = fp_offsets_used(instrs)
    next_offset_above = lambda x: min((o for o in fp_buffers if o < x), default=stack_alloc)

    fp_reg = {}  # reg -> fp_off
    has_safe = False
    has_ipc = False
    cs = callees(instrs)
    for c in cs:
        if c in SAFE_HINT: has_safe = True
        if c in IPC_HINT: has_ipc = True

    for i, (addr, raw, asm) in enumerate(instrs):
        # Track fp buffer regs
        m = RE_SUB_FP.search(asm)
        if m: fp_reg[m.group(1)] = int(m.group(2)); continue

        # Track register-to-register moves
        m = RE_MOV_REG.search(asm)
        if m:
            dst, src = m.group(1), m.group(2)
            if src in fp_reg: fp_reg[dst] = fp_reg[src]
            elif src not in fp_reg and dst in fp_reg: del fp_reg[dst]
            continue

        m = RE_BL_PLT.search(asm)
        if m and m.group(2) in UNSAFE:
            callee = m.group(2)
            r0_off = fp_reg.get("r0")
            r1_off = fp_reg.get("r1")
            r2_off = fp_reg.get("r2")
            if r0_off is not None and r0_off > 0:
                # Estimate buffer size from delta to next-larger fp offset
                # In ARM with full descending, fp-X1 buffer ends where fp-X2 (next smaller X) starts
                # Buffer at fp-228 size = (228 - next_smaller_X)
                buf_above = max((o for o in fp_buffers if o < r0_off), default=0)
                est_size = r0_off - buf_above
                # Source size estimate (if r1/r2 also fp-relative)
                src_off = r1_off if callee != "sscanf" else r2_off
                src_buf_above = None
                src_size = None
                if src_off:
                    src_buf_above = max((o for o in fp_buffers if o < src_off), default=0)
                    src_size = src_off - src_buf_above

                # interesting if: dst smaller than src OR small fixed buffer
                interesting = (est_size < 256) or (src_size and src_size > est_size)
                findings.append({
                    "call_addr": addr, "callee": callee,
                    "dst_off": r0_off, "dst_size": est_size,
                    "src_off": src_off, "src_size": src_size,
                    "stack_alloc": stack_alloc,
                    "interesting": interesting,
                    "snippet": instrs[max(0,i-6):i+1],
                })

    return findings, has_ipc, has_safe, list(cs)

def main():
    print(f"Parsing {DIS}...", file=sys.stderr)
    funcs = parse()
    print(f"  {len(funcs)} functions", file=sys.stderr)

    # Build addr→func map
    name2func = {n: (s, n, ins) for s, n, ins in funcs}

    all_findings = []
    fn_meta = {}
    for fstart, fname, instrs in funcs:
        if not instrs or "@plt" in fname:
            continue
        findings, has_ipc, has_safe, cs = scan_function(fstart, fname, instrs)
        for f in findings:
            f["fn_name"] = fname; f["fn_addr"] = fstart
            f["has_ipc"] = has_ipc; f["has_safe"] = has_safe
            all_findings.append(f)
        fn_meta[fname] = (fstart, has_ipc, has_safe, cs)

    # ----- Verify the user's known sweet spots -----
    print("\n" + "="*80)
    print("USER-PROVIDED SWEET SPOTS")
    print("="*80)
    for tn, ta in [("ddnsMain", 0x27790), ("writeVsftpdCfgFile", 0x925f8)]:
        match = [f for f in all_findings if f["fn_name"] == tn or f["fn_addr"] == ta]
        print(f"\n{tn} @ 0x{ta:x}: {len(match)} unsafe calls inside")
        for f in match:
            print(f"  {f['callee']}@0x{f['call_addr']:x} dst:fp-{f['dst_off']}(~{f['dst_size']}B)"
                  f" src:fp-{f['src_off']}{'(~'+str(f['src_size'])+'B)' if f['src_size'] else ''}")

    # ----- Likely set-handlers reachable via cmapi.setinst -----
    print("\n" + "="*80)
    print("FUNCTIONS NAMED *Set* WITH UNSAFE COPY ON SMALL STACK BUFFER (< 128 B)")
    print("="*80)
    setlike = [f for f in all_findings
               if ("Set" in f["fn_name"] or "set_" in f["fn_name"])
               and f["dst_size"] < 128
               and f["interesting"]]
    setlike.sort(key=lambda x: x["dst_size"])
    for f in setlike[:40]:
        print(f"  [{f['callee']:7s}] {f['fn_name']}@0x{f['fn_addr']:x} "
              f"dst:fp-{f['dst_off']}(~{f['dst_size']}B) "
              f"src:fp-{f['src_off']}({f['src_size']}B)" if f['src_size'] else
              f"  [{f['callee']:7s}] {f['fn_name']}@0x{f['fn_addr']:x} "
              f"dst:fp-{f['dst_off']}(~{f['dst_size']}B)")

    # ----- "src bigger than dst" — direct overflow candidates -----
    print("\n" + "="*80)
    print("CRITICAL: src buffer LARGER than dst buffer (direct copy overflow)")
    print("="*80)
    overflow = [f for f in all_findings
                if f["src_size"] and f["dst_size"] and f["src_size"] > f["dst_size"]
                and f["dst_size"] < 256]
    overflow.sort(key=lambda x: x["src_size"] - x["dst_size"], reverse=True)
    for f in overflow[:30]:
        print(f"  [{f['callee']:7s}] {f['fn_name']}@0x{f['fn_addr']:x}"
              f" dst:fp-{f['dst_off']}(~{f['dst_size']}B) ← src:fp-{f['src_off']}({f['src_size']}B)"
              f"  delta={f['src_size']-f['dst_size']}B")

    # ----- Cross-reference: function called by webd/cmapi handlers -----
    print("\n" + "="*80)
    print("FUNCTIONS THAT CONTAIN *Set* AND CALL strcpy/sprintf, ALSO ECHOED BY CMAPI/WEBD")
    print("="*80)
    # heuristic: look for callees in callgraph from any "*WebdGet*"/"*WebdSet*"/"cspd_main" entry
    # We don't have full call-graph but can check the function names of callers
    web_callers = set()
    for f in funcs:
        n = f[1]
        if any(p in n for p in ("Webd", "webd", "Cmapi", "cmapi")):
            for _,_,asm in f[2]:
                m = RE_BL.search(asm)
                if m: web_callers.add(m.group(2))
    web_reachable = [f for f in setlike if f["fn_name"] in web_callers]
    for f in web_reachable[:20]:
        print(f"  {f['fn_name']}@0x{f['fn_addr']:x} — {f['callee']}@0x{f['call_addr']:x}")

if __name__ == "__main__":
    main()
