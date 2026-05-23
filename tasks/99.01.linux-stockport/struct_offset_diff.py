#!/usr/bin/env python3
"""
Compare stock kernel function dumps (from /proc/tm/shell) vs our compiled
kernel's same functions. Extract ldr/str immediates from both. Pair them
by position in the function and emit a stock_offset → ours_offset map.

This map is what we'd need to patch in plat-zxylzb_9128S.ko so its
hardcoded stock offsets become our offsets.
"""
import re, os, struct, sys
from pathlib import Path

DUMP_DIR = Path("/tmp/stock_dumps")

def parse_stock_dump(path):
    """Returns list of (offset_in_fn, opcode_int) tuples."""
    insns = []
    for line in Path(path).read_text().splitlines():
        m = re.match(r"\+0x([0-9a-f]+): 0x([0-9a-f]{8})$", line)
        if m:
            insns.append((int(m.group(1), 16), int(m.group(2), 16)))
    return insns

def parse_ours_dump(path):
    """Parse objdump -d output. Returns list of (offset_in_fn, opcode_int)."""
    insns = []
    base = None
    for line in Path(path).read_text().splitlines():
        m = re.match(r"\s*([0-9a-f]+):\s+([0-9a-f]{8})\s", line)
        if m:
            addr = int(m.group(1), 16)
            if base is None: base = addr
            insns.append((addr - base, int(m.group(2), 16)))
    return insns

def decode_ldr_str_imm(opcode):
    """If `ldr/str Rd, [Rn, #imm]` return (Rd, Rn, imm, is_load, is_byte).
    Else None. Only handles unconditional A=I=0 P=1 W=0 immediate offset."""
    cond = (opcode >> 28) & 0xF
    if cond != 0xE: return None
    op = (opcode >> 24) & 0xF
    if op != 0x5: return None  # type-1 ldr/str
    p = (opcode >> 24) & 1
    u = (opcode >> 23) & 1
    b = (opcode >> 22) & 1
    w = (opcode >> 21) & 1
    l = (opcode >> 20) & 1
    rn = (opcode >> 16) & 0xF
    rd = (opcode >> 12) & 0xF
    imm = opcode & 0xFFF
    if not u: imm = -imm
    return (rd, rn, imm, bool(l), bool(b))

def extract_imms(insns, only_reg=None):
    """For each ldr/str-imm insn, return (position_index, imm, opcode)."""
    out = []
    for i, (off, op) in enumerate(insns):
        d = decode_ldr_str_imm(op)
        if d is None: continue
        rd, rn, imm, l, b = d
        if only_reg is not None and rn != only_reg: continue
        out.append((i, imm, op, rd, rn, l, b))
    return out

def pair_by_position(stock, ours):
    """Match ldr/str positions between stock and ours. Each entry is
    (idx, imm, op, rd, rn, l, b). Output (idx, s_imm, o_imm, rn)."""
    s_dict = {e[0]: e[1:] for e in stock}
    o_dict = {e[0]: e[1:] for e in ours}
    pairs = []
    for i in sorted(set(s_dict) & set(o_dict)):
        s = s_dict[i]  # (imm, op, rd, rn, l, b)
        o = o_dict[i]
        # Both must be same kind: same rn (base reg), same load/store, same width
        s_imm, s_op, s_rd, s_rn, s_l, s_b = s
        o_imm, o_op, o_rd, o_rn, o_l, o_b = o
        if s_rn != o_rn or s_l != o_l or s_b != o_b:
            continue
        if s_imm != o_imm:
            pairs.append((i, s_imm, o_imm, s_rn))
    return pairs

def offsets_by_rn(insns):
    """Returns dict rn → sorted list of (idx, imm) for ldr/str-imm insns."""
    out = {}
    for i, (off, op) in enumerate(insns):
        d = decode_ldr_str_imm(op)
        if d is None: continue
        rd, rn, imm, l, b = d
        out.setdefault(rn, []).append((i, imm))
    return {k: sorted(v) for k, v in out.items()}

def main():
    if not DUMP_DIR.exists():
        print(f"ERROR: {DUMP_DIR} missing", file=sys.stderr); sys.exit(1)

    fns = []
    for s in DUMP_DIR.glob("*_stock.txt"):
        fn = s.stem.replace("_stock", "")
        o = DUMP_DIR / f"{fn}_ours.txt"
        if o.exists():
            fns.append((fn, s, o))

    print(f"# Comparing {len(fns)} function pairs (set-based)\n")

    # For each rn, collect (stock_offsets, our_offsets) per function
    rn_stock = {}
    rn_ours  = {}
    for fn, s_path, o_path in fns:
        s_insns = parse_stock_dump(s_path)
        o_insns = parse_ours_dump(o_path)
        if not s_insns or not o_insns: continue
        s_by = offsets_by_rn(s_insns)
        o_by = offsets_by_rn(o_insns)
        for rn in set(s_by) | set(o_by):
            rn_stock.setdefault(rn, set()).update(imm for (_, imm) in s_by.get(rn, []))
            rn_ours.setdefault(rn, set()).update(imm for (_, imm) in o_by.get(rn, []))

    for rn in sorted(rn_stock):
        s_set = sorted(rn_stock.get(rn, set()))
        o_set = sorted(rn_ours.get(rn, set()))
        common = sorted(set(s_set) & set(o_set))
        s_only = sorted(set(s_set) - set(o_set))
        o_only = sorted(set(o_set) - set(s_set))
        if not (s_only or o_only): continue  # skip if perfectly matched
        print(f"\n## Rn = r{rn} ({len(common)} common, {len(s_only)} stock-only, {len(o_only)} ours-only)")
        print(f"  stock-only offsets: {', '.join(f'0x{x:03x}' for x in s_only[:20])}")
        print(f"  ours-only  offsets: {', '.join(f'0x{x:03x}' for x in o_only[:20])}")
        # Heuristic mapping: pair stock-only with ours-only by closest distance
        if s_only and o_only:
            print(f"  heuristic stock→ours pairing (by closest):")
            for s in s_only:
                best = min(o_only, key=lambda o: abs(o - s))
                if abs(best - s) <= 32:
                    print(f"    0x{s:03x} → 0x{best:03x}  (delta {best-s:+d})")

if __name__ == "__main__":
    main()
