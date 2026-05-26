#!/usr/bin/env python3
"""gen_stock_bursts.py — refactor #38 Phase 8a

Scans zx_stock_table.h and emits a sibling header zx_stock_bursts.h that
expresses the same 22363 writes as a sequence of OPERATIONS:

  - "burst": contiguous +4 stride run of length ≥ 4 in a single window
             (pon_early or base). The run's values become a static const
             u32 array; the driver writes them via __iowrite32_copy().
  - "singleton/short": runs of length 1-3 stay as direct writel() calls
                       in a flat (off, val) table.

The two tables together let the driver replay the whole stock init in
~8 k operations instead of 22 k. More importantly, each big burst gets a
name and a comment naming the target RAM region — which is what netdev
reviewers want.

Phase 8a goal: GENERATE the header; the driver doesn't use it yet (it
keeps walking zx_stock_init_table[]). The driver only adds diagnostics
that count how the runs distribute per block, so we can verify the
script's classification matches what the chip is doing.

Run from repo root.
"""
import re
from pathlib import Path

SRC = Path("linux-v6.6/drivers/net/ethernet/zte/zx_stock_table.h")
DST = Path("linux-v6.6/drivers/net/ethernet/zte/zx_stock_bursts.h")

MIN_BURST_LEN = 4

# Block ranges (must mirror annotate_stock_table.py)
BLOCKS = [
    ("PON_LOW",  -0x1c0000, -0x180000, "pon_early"),
    ("PON_B",    -0x180000, -0x140000, "pon_early"),
    ("PON_TAIL", -0x140000,  0,        "pon_early"),
    ("NPP",       0,         0x40000,  "base"),
    ("NPP_AUX",   0xcc000,   0xfd000,  "base"),
    ("TM",        0x180000,  0x1c0000, "base"),
    ("PP_FUC",    0x1c0000,  0x1e4000, "base"),
]

# Blocks that have been moved out into explicit C init functions in the
# driver. Their writes are SKIPPED here so we don't double-apply them.
# The driver must call zx_<block>_init() in the same relative position
# in probe to preserve original write order.
SKIP_BLOCKS = {
    "PON_LOW",  # zx_pon_low_init() — refactor #38 Phase 9a
    "NPP_AUX",  # zx_npp_aux_init() — refactor #38 Phase 9c
}

# Sub-block ranges to filter (start_off, byte_len). Used when an
# explicit init handles a slice of a block without owning the whole
# thing. Same effect as SKIP_BLOCKS but at offset granularity.
# Driver invokes the explicit init around the still-present block.
SKIP_RANGES = [
    # Phase 9d: TM per-instance 64-entry table replicated 16 times at
    # base 0x190240 + i*0x400 (i in 0..15), 0x100 bytes each.
    *[(0x190240 + i * 0x400, 64 * 4) for i in range(16)],
    # Phase 9e: PON_TAIL big lookup RAM init — 4082 entries at
    # pon_early off=-0xfffc0..-0xfbff8 (16 KB). 4080× 0x4bef + 2 footer
    # words. Becomes zx_pon_tail_lookup_init().
    (-0xfffc0, 4082 * 4),
]


def window(off):
    return "pon_early" if off < 0 else "base"


def classify_block(off):
    for name, lo, hi, _ in BLOCKS:
        if lo <= off < hi:
            return name
    return "UNKNOWN"


def parse_entries():
    text = SRC.read_text()
    entry_re = re.compile(
        r"/\*\s*(\d+)\*/\s+\{\s*(-?0x[0-9a-fA-F]+)\s*,\s*(0x[0-9a-fA-F]+)\s*\}"
    )
    entries = []
    for m in entry_re.finditer(text):
        off_s = m.group(2)
        off = -int(off_s[1:], 16) if off_s.startswith("-") else int(off_s, 16)
        val = int(m.group(3), 16)
        entries.append((off, val))
    return entries


def in_skip_range(off):
    """True if off falls in any (start, len) range in SKIP_RANGES."""
    for start, length in SKIP_RANGES:
        if start <= off < start + length:
            return True
    return False


def detect_runs(entries):
    """Walk entries; yield (start_idx, end_idx, kind) tuples.

    kind: "burst" if length >= MIN_BURST_LEN and strict +4 within one window,
          "short" otherwise (length 1..MIN_BURST_LEN-1).
    """
    n = len(entries)
    runs = []
    i = 0
    while i < n:
        j = i + 1
        while j < n:
            same_win = window(entries[j][0]) == window(entries[j - 1][0])
            contig = entries[j][0] == entries[j - 1][0] + 4
            if not (same_win and contig):
                break
            j += 1
        kind = "burst" if (j - i) >= MIN_BURST_LEN else "short"
        runs.append((i, j, kind))
        i = j
    return runs


def main():
    entries = parse_entries()
    runs = detect_runs(entries)

    # Filter out runs that belong to SKIP_BLOCKS or fall in SKIP_RANGES
    # (both handled by explicit C init in the driver).
    skipped_runs = 0
    skipped_entries = 0
    kept_runs = []
    for s, e, kind in runs:
        first_off = entries[s][0]
        block = classify_block(first_off)
        if block in SKIP_BLOCKS:
            skipped_runs += 1
            skipped_entries += (e - s)
            continue
        # SKIP_RANGES filtering: a contiguous run either entirely falls
        # inside one skip-range or doesn't intersect any. Bursts are
        # uniform stride so a single-point check is enough.
        if in_skip_range(first_off):
            skipped_runs += 1
            skipped_entries += (e - s)
            continue
        kept_runs.append((s, e, kind))
    runs = kept_runs

    n_burst = sum(1 for *_, k in runs if k == "burst")
    n_short = sum(1 for *_, k in runs if k == "short")
    entries_in_burst = sum(e - s for s, e, k in runs if k == "burst")
    entries_in_short = sum(e - s for s, e, k in runs if k == "short")

    out = []
    out.append("/* zx_stock_bursts.h — auto-generated from zx_stock_table.h by")
    out.append(" *   tasks/00.01.eth-driver/scripts/gen_stock_bursts.py")
    out.append(" *")
    out.append(" * Refactor #38 Phase 8: re-expresses the linear stock_init_table")
    out.append(" * as a stream of OPERATIONS — large contiguous runs as static")
    out.append(" * const u32 arrays (target of __iowrite32_copy), short runs as")
    out.append(" * (off, val) singletons. Same writes, dramatically fewer operations.")
    out.append(" *")
    out.append(f" * Source entries : {len(entries)}")
    if SKIP_BLOCKS:
        out.append(f" * Skipped blocks : {sorted(SKIP_BLOCKS)} ({skipped_entries} entries via {skipped_runs} runs)")
        out.append(f" *                  → handled by explicit zx_<block>_init() in the driver")
    out.append(f" * Bursts (≥{MIN_BURST_LEN} entries): {n_burst}, covering {entries_in_burst} entries")
    out.append(f" * Short runs    : {n_short}, covering {entries_in_short} entries")
    out.append(f" * Total ops     : {n_burst + entries_in_short} (vs {len(entries) - skipped_entries} replayed)")
    out.append(" */")
    out.append("#ifndef ZX_STOCK_BURSTS_H")
    out.append("#define ZX_STOCK_BURSTS_H")
    out.append("")
    out.append("#include <linux/types.h>")
    out.append("")
    out.append("/* Burst kind — encoded in the master descriptor table */")
    out.append("#define ZX_BURST_KIND_RUN     0  /* __iowrite32_copy(base + off, data, len) */")
    out.append("#define ZX_BURST_KIND_SINGLE  1  /* writel(val, base + off) */")
    out.append("")
    out.append("/* Window selector — which ioremap'd base this op targets */")
    out.append("#define ZX_BURST_WIN_BASE      0")
    out.append("#define ZX_BURST_WIN_PON_EARLY 1")
    out.append("")
    out.append("struct zx_stock_op {")
    out.append("\tu32 off_or_addr;      /* base offset (for SINGLE) or window-relative byte (for RUN) */")
    out.append("\tu32 val_or_len;       /* val (SINGLE) or length in u32 (RUN) */")
    out.append("\tconst u32 *data;      /* NULL for SINGLE, points into bursts_data[] for RUN */")
    out.append("\tu8 kind;")
    out.append("\tu8 window;")
    out.append("\tu16 _pad;")
    out.append("} __packed;")
    out.append("")

    # Emit per-burst data arrays
    burst_arrays = []
    for run_idx, (s, e, kind) in enumerate(runs):
        if kind != "burst":
            continue
        first_off = entries[s][0]
        win = window(first_off)
        arr_name = f"zx_burst_{run_idx:04d}_data"
        # Compute window-relative byte offset to use at apply time
        if win == "pon_early":
            win_byte_off = first_off + 0x1c0000  # convert signed to unsigned window byte
        else:
            win_byte_off = first_off
        block = classify_block(first_off)
        out.append(f"/* burst #{run_idx}: {block}/{win} off={first_off:#x} → {entries[e-1][0]:#x}"
                   f" ({e-s} regs) */")
        out.append(f"static const u32 {arr_name}[{e - s}] = {{")
        vals = [entries[s + k][1] for k in range(e - s)]
        for line_start in range(0, len(vals), 8):
            chunk = vals[line_start:line_start + 8]
            out.append("\t" + ", ".join(f"{v:#010x}" for v in chunk) + ",")
        out.append("};")
        out.append("")
        burst_arrays.append((run_idx, arr_name, win, win_byte_off, e - s, block))

    # Emit master ops table
    out.append("/* Master operation table — replay in order. Each entry is either a")
    out.append(" * single writel() or a contiguous run flushed via __iowrite32_copy(). */")
    total_ops = n_burst + entries_in_short
    out.append(f"static const struct zx_stock_op zx_stock_ops[{total_ops}] = {{")
    burst_lookup = {ri: (an, win, wbo, ln, blk) for ri, an, win, wbo, ln, blk in burst_arrays}
    op_idx = 0
    cur_block_label = None
    # Track per-block op index ranges so the driver can walk per-block
    block_op_ranges = {}  # block_name → [start, end) into zx_stock_ops[]
    for run_idx, (s, e, kind) in enumerate(runs):
        first_off = entries[s][0]
        block = classify_block(first_off)
        if block != cur_block_label:
            # Close the previous block's range
            if cur_block_label is not None:
                block_op_ranges[cur_block_label] = (
                    block_op_ranges[cur_block_label], op_idx,
                )
            block_op_ranges[block] = op_idx  # tentative start
            out.append(f"\t/* ──── {block} (ops {op_idx}..) ──── */")
            cur_block_label = block
        if kind == "burst":
            arr_name, win, win_byte_off, ln, _blk = burst_lookup[run_idx]
            win_const = "ZX_BURST_WIN_PON_EARLY" if win == "pon_early" else "ZX_BURST_WIN_BASE"
            out.append(f"\t{{ {win_byte_off:#10x}, {ln:5d}, {arr_name}, "
                       f"ZX_BURST_KIND_RUN,    {win_const} }}, /* #{run_idx} */")
            op_idx += 1
        else:
            for k in range(s, e):
                off, val = entries[k]
                if off < 0:
                    win_const = "ZX_BURST_WIN_PON_EARLY"
                    win_byte_off = off + 0x1c0000
                else:
                    win_const = "ZX_BURST_WIN_BASE"
                    win_byte_off = off
                out.append(f"\t{{ {win_byte_off:#10x}, {val:#010x}, NULL,        "
                           f"ZX_BURST_KIND_SINGLE, {win_const} }},")
                op_idx += 1
    out.append("};")
    # Close the last block's range
    if cur_block_label is not None:
        block_op_ranges[cur_block_label] = (
            block_op_ranges[cur_block_label], op_idx,
        )
    out.append("")
    out.append(f"#define ZX_STOCK_OPS_LEN {total_ops}")
    out.append("")
    out.append("/* Per-block slice indices into zx_stock_ops[]. Drivers walk one")
    out.append(" * block at a time so explicit zx_<block>_init() calls (Phase 9+)")
    out.append(" * can be interleaved at the right point in the init sequence. */")
    for name, lo, hi, target in BLOCKS:
        if name in block_op_ranges:
            s, e = block_op_ranges[name]
            out.append(f"#define ZX_STOCK_OPS_{name}_START {s}")
            out.append(f"#define ZX_STOCK_OPS_{name}_END   {e}")
            out.append(f"#define ZX_STOCK_OPS_{name}_LEN   {e - s}")
        elif name in SKIP_BLOCKS:
            out.append(f"/* {name}: handled by explicit zx_<block>_init() — no ops emitted */")
    out.append("")
    out.append("/* Sanity: total individual register writes when replayed must equal")
    out.append(f" * the original {len(entries)} entries minus the {skipped_entries} entries in")
    out.append(f" * blocks handled by explicit zx_<block>_init() functions. */")
    out.append(f"#define ZX_STOCK_OPS_WRITES_EXPECTED {len(entries) - skipped_entries}")
    out.append("")
    out.append("#endif /* ZX_STOCK_BURSTS_H */")

    DST.write_text("\n".join(out) + "\n")
    print(f"wrote {DST} ({DST.stat().st_size} bytes)")
    print()
    print(f"Source entries   : {len(entries)}")
    print(f"Bursts (≥{MIN_BURST_LEN})   : {n_burst} runs, {entries_in_burst} entries"
          f" ({100*entries_in_burst/len(entries):.1f}%)")
    print(f"Short runs (<{MIN_BURST_LEN}): {n_short} runs, {entries_in_short} entries"
          f" ({100*entries_in_short/len(entries):.1f}%)")
    print(f"Total ops        : {total_ops} (vs {len(entries)} writes,"
          f" {len(entries)/total_ops:.1f}× reduction)")


if __name__ == "__main__":
    main()
