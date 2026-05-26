#!/usr/bin/env python3
"""annotate_stock_table.py — refactor #38 Phase 5

Regenerates linux-v6.6/.../zx_stock_table.h with SECTION COMMENTS labeling
each contiguous block of entries by HW sub-block (PON, NPP, TM, PP,
IDM, CLA, ...). This is the SEMANTIC step on top of Phase 3's
mechanical embed.

Block boundaries derived from:
  - tasks/00.10.02.re-stock-kmods/findings/HW_BLOCKS_INVENTORY.md
  - linux-v6.6/.../zx-fpga-reg-tables.h descriptor offsets
  - Driver's TM_REG_*, PP_BRG_BASE, IDM_REG_* macros
  - Gap analysis of stock.bin offsets (>64 KB gap → block boundary)

The driver uses two MMIO windows:
  - eth->base       = ioremap(0x921c0000, ...) — NPP at offset 0
  - eth->pon_early  = ioremap(0x92000000, ...) — PON at offset 0,
                       so negative `off` arg means pon_early + (off + 0x1c0000)

Physical-address view (offset relative to 0x92000000):
   0x000000..0x040000   PON_LOW          (pon_early off=-0x1c0000..-0x180000)
   0x040000..0x080000   PON_SECONDARY    (pon_early off=-0x180000..-0x140000)
   0x080000..0x1c0000   reserved / partial regs (-0x140000..0)
   0x1c0000..0x200000   NPP              (base off=0..0x40000)
   0x200000..0x340000   gap (no block known here yet)
   0x340000..0x380000   TM               (base off=0x180000..0x1c0000)
   0x380000..0x3c0000   PP               (base off=0x1c0000..0x200000)

This script does NOT re-derive the writes (Phase 3 did that). It just
re-emits the same table grouped by section with named headers.

Run from repo root.
"""
import struct
from pathlib import Path

SRC = Path("tasks/00.01.eth-driver/initramfs/lib/firmware/zx-replay/stock.bin")
# stock.bin was deleted in Phase 3. Source-of-truth is the embedded header.
HDR = Path("linux-v6.6/drivers/net/ethernet/zte/zx_stock_table.h")
OUT = HDR  # rewrites in place

# Block ranges expressed in driver-offset terms (signed s32 off from
# either base or pon_early; the *_PON_EARLY ranges use negative off).
# Closed-open intervals.
BLOCKS = [
    # (name,           lo,            hi,            target_window,        notes)
    ("PON_LOW",        -0x1c0000,     -0x180000,     "pon_early",         "PON low control regs (sbrg/spa/dpa init)"),
    ("PON_B",          -0x180000,     -0x140000,     "pon_early",         "secondary PON block"),
    ("PON_TAIL",       -0x140000,      0,            "pon_early",         "remaining PON regs before NPP boundary"),
    ("NPP",             0,             0x40000,      "base",              "Network Packet Processor (npp_*)"),
    ("NPP_TAIL",        0x40000,       0xcc000,      "base",              "NPP overflow / IDM front-end"),
    ("NPP_AUX",         0xcc000,       0xfd000,      "base",              "NPP auxiliary regs"),
    ("TM",              0x180000,      0x1c0000,     "base",              "Traffic Manager (tm_*)"),
    ("PP_FUC",          0x1c0000,      0x1e4000,     "base",              "Packet Processor function table (fuc_*)"),
]


def classify(off: int) -> tuple[str, str]:
    """Return (block_name, target_window) for a stock-table offset."""
    for name, lo, hi, target, _ in BLOCKS:
        if lo <= off < hi:
            return name, target
    return ("UNKNOWN", "?")


def main():
    # Read the existing embedded table — it's the source of truth now
    # that stock.bin is deleted.
    lines = HDR.read_text().splitlines()

    # Pull the array body lines (`{...},`) — they have a structured form.
    entries = []
    for ln in lines:
        s = ln.strip()
        # /* NNNN*/ {{...,...},{...,...},...,
        if s.startswith("/*") and "*/" in s and "{" in s:
            # Strip the comment prefix
            body = s.split("*/", 1)[1]
            # Find pairs of {off, val}
            i = 0
            while True:
                lb = body.find("{", i)
                if lb < 0:
                    break
                rb = body.find("}", lb)
                if rb < 0:
                    break
                pair = body[lb + 1:rb]
                a, b = [p.strip() for p in pair.split(",", 1)]
                entries.append((int(a, 16) if "0x" in a else int(a),
                                int(b, 16) if "0x" in b else int(b)))
                i = rb + 1
    n = len(entries)
    print(f"parsed {n} entries from {HDR}")

    # Group entries by classify(off) — but keep ORIGINAL order so writes
    # don't reorder.
    out = []
    out.append("/* zx_stock_table.h — auto-generated from stock.bin by")
    out.append(" *   tasks/00.01.eth-driver/scripts/gen_stock_table.py")
    out.append(" * then annotated by")
    out.append(" *   tasks/00.01.eth-driver/scripts/annotate_stock_table.py")
    out.append(" *")
    out.append(" * Replaces firmware_request(\"zx-replay/stock.bin\") with a static C array.")
    out.append(f" * {n} entries × 8 bytes = {n*8} bytes (~{n*8//1024} KB .rodata).")
    out.append(" *")
    out.append(" * Phase 5 annotation: each section comment maps a contiguous range of")
    out.append(" * (off, val) writes to its HW sub-block, derived from")
    out.append(" *   tasks/00.10.02.re-stock-kmods/findings/HW_BLOCKS_INVENTORY.md.")
    out.append(" * Section labels are a Phase 6 stepping stone — once each block is split")
    out.append(" * into its own per-block init function, this table will shrink to only the")
    out.append(" * regs that haven't been moved out yet.")
    out.append(" */")
    out.append("#ifndef ZX_STOCK_TABLE_H")
    out.append("#define ZX_STOCK_TABLE_H")
    out.append("")
    out.append("#include <linux/types.h>")
    out.append("")
    out.append("struct zx_stock_entry { s32 off; u32 val; } __packed;")
    out.append("")
    out.append(f"static const struct zx_stock_entry zx_stock_init_table[{n}] = {{")

    cur_section = None
    section_counts = {}
    section_starts = {}    # name -> first index in zx_stock_init_table
    section_ends = {}      # name -> first index AFTER section (exclusive)
    for i, (off, val) in enumerate(entries):
        name, target = classify(off)
        if name != cur_section:
            if cur_section is not None:
                section_ends[cur_section] = i
                out.append(f"\t/* end {cur_section} ({section_counts[cur_section]} regs) */")
            block_info = next((b for b in BLOCKS if b[0] == name), None)
            note = block_info[4] if block_info else "out-of-known-range"
            out.append("")
            out.append(f"\t/* ──── {name} ({target}, {note}) ──── */")
            cur_section = name
            section_starts[name] = i
        section_counts[name] = section_counts.get(name, 0) + 1
        out.append(f"\t/*{i:5d}*/ {{{off:#11x}, {val:#010x}}},")

    if cur_section:
        section_ends[cur_section] = n
        out.append(f"\t/* end {cur_section} ({section_counts[cur_section]} regs) */")

    out.append("};")
    out.append("")
    out.append(f"#define ZX_STOCK_INIT_TABLE_LEN {n}")
    out.append("")
    out.append("/* Phase 6: per-block slice indices into zx_stock_init_table[]. */")
    out.append("/* A block's writes are entries [START, END) — pass to zx_replay_stock_block(). */")
    for name, lo, hi, target, _ in BLOCKS:
        if name in section_starts:
            s = section_starts[name]
            e = section_ends[name]
            out.append(f"#define ZX_STOCK_{name}_START {s}")
            out.append(f"#define ZX_STOCK_{name}_END   {e}")
            out.append(f"#define ZX_STOCK_{name}_LEN   {e - s}  /* target: {target} */")
    out.append("")
    out.append("#endif /* ZX_STOCK_TABLE_H */")

    OUT.write_text("\n".join(out) + "\n")
    print(f"wrote {OUT} ({OUT.stat().st_size} bytes)")
    print()
    print("Section breakdown:")
    for name, _, _, target, _ in BLOCKS:
        cnt = section_counts.get(name, 0)
        if cnt:
            print(f"  {name:<14}  ({target:<10}) {cnt:6d} regs")
    unk = section_counts.get("UNKNOWN", 0)
    if unk:
        print(f"  UNKNOWN              {unk:6d} regs (re-check BLOCKS ranges)")


if __name__ == "__main__":
    main()
