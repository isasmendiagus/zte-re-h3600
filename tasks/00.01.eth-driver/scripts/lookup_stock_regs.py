#!/usr/bin/env python3
"""lookup_stock_regs.py — refactor #38 Phase 7

For each entry in zx_stock_init_table[], try to identify the underlying
HW register by matching its offset against the descriptor tables in
linux-v6.6/.../zx-fpga-reg-tables.h.

Descriptor entries have:
  base_off : starting WORD index from fpga_base 0x92000000
  stride   : added per sub_idx
  max_sub_idx: last valid sub_idx (so reg covers [base_off, base_off + stride*max_sub_idx])
  reg_id   : numeric identifier within its table
  mode     : 1=R 2=W 3=RW
  mask/shift: bit-field within the 32-bit word (multiple regs can share base_off)

stock_table entry off is BYTE offset:
  if off < 0  : pon_early + (off + 0x1c0000)  → phys 0x92000000 + (off + 0x1c0000)
                so fpga byte = off + 0x1c0000
  if off >= 0 : eth->base   + off              → phys 0x921c0000 + off
                so fpga byte = off + 0x1c0000
  → in BOTH cases: fpga_byte = off + 0x1c0000, fpga_word = fpga_byte >> 2

Run from repo root.
"""
import re
from pathlib import Path
from collections import defaultdict, Counter

ROOT = Path(".")
TBL_HDR = ROOT / "linux-v6.6/drivers/net/ethernet/zte/zx-fpga-reg-tables.h"
STOCK = ROOT / "linux-v6.6/drivers/net/ethernet/zte/zx_stock_table.h"
OUT = ROOT / "tasks/00.01.eth-driver/findings/stock_table_reg_names.txt"


def parse_descriptors():
    """Parse all descriptor entries from zx-fpga-reg-tables.h"""
    text = TBL_HDR.read_text()
    table_re = re.compile(r"static const struct zx_fpga_reg (\w+)\[\]")
    desc_re = re.compile(
        r"\.reg_id=\s*(\d+),\s*\.mode=(\d+),\s*"
        r"\.base_off=0x([0-9a-f]+),\s*"
        r"\.mask=0x([0-9a-f]+),\s*"
        r"\.shift=\s*(\d+),\s*"
        r"\.max_sub_idx=\s*(\d+),\s*"
        r"\.stride=0x([0-9a-f]+)"
    )
    cur = None
    descs = []  # (table, reg_id, mode, base_off_word, mask, shift, max_sub_idx, stride_word)
    for line in text.splitlines():
        tm = table_re.search(line)
        if tm:
            cur = tm.group(1)
            continue
        dm = desc_re.search(line)
        if dm and cur:
            descs.append((
                cur,
                int(dm.group(1)),
                int(dm.group(2)),
                int(dm.group(3), 16),
                int(dm.group(4), 16),
                int(dm.group(5)),
                int(dm.group(6)),
                int(dm.group(7), 16),
            ))
    return descs


def parse_stock_entries():
    """Parse (idx, off, val) tuples from zx_stock_table.h"""
    text = STOCK.read_text()
    entry_re = re.compile(r"/\*\s*(\d+)\*/\s+\{\s*(-?0x[0-9a-fA-F]+|0x[0-9a-fA-F]+)\s*,\s*(0x[0-9a-fA-F]+)\s*\}")
    entries = []
    for m in entry_re.finditer(text):
        idx = int(m.group(1))
        # off can be negative — handle both
        off_s = m.group(2)
        off = int(off_s, 16) if "x" in off_s else int(off_s)
        # Python int() with negative hex needs explicit sign
        if off_s.startswith("-"):
            off = -int(off_s[1:], 16)
        val = int(m.group(3), 16)
        entries.append((idx, off, val))
    return entries


def build_lookup(descs):
    """Build a dict: fpga_word_index → list of (table, reg_id, sub_idx, mask, shift)"""
    lookup = defaultdict(list)
    for tbl, rid, mode, base_off, mask, shift, max_sub_idx, stride in descs:
        for sub in range(max_sub_idx + 1):
            addr = base_off + stride * sub
            lookup[addr].append((tbl, rid, sub, mask, shift, mode))
    return lookup


def main():
    descs = parse_descriptors()
    entries = parse_stock_entries()
    lookup = build_lookup(descs)
    print(f"parsed {len(descs)} descriptors, {len(entries)} stock entries")
    print(f"unique fpga word addresses with names: {len(lookup)}")

    OUT.parent.mkdir(parents=True, exist_ok=True)
    lines = []
    lines.append("Stock-table register name mapping")
    lines.append("=================================")
    lines.append("")
    lines.append("Each entry of zx_stock_init_table[] (zx_stock_table.h) is")
    lines.append("written by the driver during probe. This file maps each entry")
    lines.append("index → its underlying HW register, where derivable from the")
    lines.append("descriptor tables in zx-fpga-reg-tables.h.")
    lines.append("")
    lines.append("Mapping rule:")
    lines.append("  fpga_byte = off + 0x1c0000  (whether off is negative pon_early")
    lines.append("                                or non-negative base — same math)")
    lines.append("  fpga_word = fpga_byte >> 2")
    lines.append("")
    lines.append("Match against descriptor entries: base_off + stride*sub_idx == fpga_word.")
    lines.append("Multiple regs can share the same word (packed bit-fields); shown as alts.")
    lines.append("")

    hit = 0
    miss = 0
    per_table_hits = Counter()
    for idx, off, val in entries:
        fpga_byte = off + 0x1c0000
        fpga_word = fpga_byte >> 2
        descs_here = lookup.get(fpga_word, [])
        if descs_here:
            hit += 1
            for tbl, rid, sub, mask, shift, mode in descs_here:
                per_table_hits[tbl] += 1
            # Pick the first match to print succinctly
            tbl, rid, sub, mask, shift, mode = descs_here[0]
            mode_str = {1: "R", 2: "W", 3: "RW"}.get(mode, "?")
            extra = f" + {len(descs_here)-1} bitfield alts" if len(descs_here) > 1 else ""
            lines.append(f"  /*{idx:5d}*/ off={off:#11x} val={val:#010x}  "
                         f"→ {tbl}[reg_id={rid}, sub={sub}] {mode_str}"
                         f" mask={mask:#x} shift={shift}{extra}")
        else:
            miss += 1
            # Don't emit every miss to keep file readable; periodic sample
            if (miss % 500) == 1:
                lines.append(f"  /*{idx:5d}*/ off={off:#11x} val={val:#010x}  → UNKNOWN (fpga word {fpga_word:#x})")

    lines.append("")
    lines.append("=" * 50)
    lines.append("Summary:")
    lines.append(f"  total entries:    {len(entries)}")
    lines.append(f"  matched:          {hit} ({hit*100/len(entries):.1f}%)")
    lines.append(f"  unmatched:        {miss} ({miss*100/len(entries):.1f}%)")
    lines.append("")
    lines.append("Hits per descriptor table:")
    for tbl, cnt in per_table_hits.most_common():
        lines.append(f"  {tbl:<25} {cnt:6d}")

    OUT.write_text("\n".join(lines) + "\n")
    print(f"wrote {OUT} ({OUT.stat().st_size} bytes)")
    print()
    print(f"matched: {hit}/{len(entries)} = {hit*100/len(entries):.1f}%")
    print(f"unmatched: {miss} (sample every 500 shown in output)")
    print()
    print("Hits per table:")
    for tbl, cnt in per_table_hits.most_common():
        print(f"  {tbl:<25} {cnt:6d}")


if __name__ == "__main__":
    main()
