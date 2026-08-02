#!/usr/bin/env python3
"""Generate C init functions from zx_stock_bursts.h pattern analysis.

Parses the auto-generated burst data, identifies repeated patterns
(stride-identical register writes), and generates explicit C init
functions to replace the opaque hex dump. Outputs:

  1. zx_stock_bursts.h  — deduplicated (bursts replaced by calls to init funcs)
  2. zx-eth-init-gen.c  — generated C init functions
"""

import re, sys
from pathlib import Path
from collections import defaultdict

BURST_HEADER = Path(sys.argv[1]) if len(sys.argv) > 1 else Path(
    "linux-v6.6/drivers/net/ethernet/zte/zx_stock_bursts.h"
)
OUT_BURSTS = Path(sys.argv[2]) if len(sys.argv) > 2 else Path("zx_stock_bursts_gen.h")
OUT_INIT   = Path(sys.argv[3]) if len(sys.argv) > 3 else Path("zx-eth-init-gen.c")

content = BURST_HEADER.read_text()

# Parse burst definitions:  /* burst #N: WINDOW off=START -> END (COUNT regs) */
# Followed by: static const u32 zx_burst_N_data[COUNT] = { val0, val1, ... };
burst_pat = re.compile(
    r'/\*\s*burst\s*#(\d+):\s*([^*]+?)\s*\*/\s*'
    r'static\s+const\s+u32\s+zx_burst_(\d+)_data\[(\d+)\]\s*=\s*\{([^}]+)\};',
    re.DOTALL
)

bursts = {}  # id -> {window, start_off, end_off, count, values, text}
for m in burst_pat.finditer(content):
    bid = int(m.group(1))
    comment = m.group(2).strip()
    _bid2 = int(m.group(3))  # should match bid
    count = int(m.group(4))
    vals_str = m.group(5)
    vals = [v.strip() for v in vals_str.split(',') if v.strip()]
    full_text = m.group(0)

    # Parse comment: WINDOW off=START -> END (COUNT regs)
    cm = re.match(r'(\S+)\s+off=(-?0x[0-9a-f]+)\s*→\s*(-?0x[0-9a-f]+)', comment)
    if cm:
        window = cm.group(1)
        start_off = cm.group(2)
        end_off = cm.group(3)
    else:
        window = comment.split()[0] if comment else "???"
        start_off = "0x0"
        end_off = "0x0"

    bursts[bid] = {
        'id': bid, 'window': window, 'start_off': start_off,
        'end_off': end_off, 'count': count, 'vals': tuple(vals),
        'text': full_text
    }

# Group by (window, vals) to find identical patterns
pattern_groups = defaultdict(list)
for bid, b in bursts.items():
    key = (b['window'], b['vals'])
    pattern_groups[key].append(b)

# Filter: groups with >= 4 identical blocks → candidate for dedup
dedup_candidates = {k: v for k, v in pattern_groups.items() if len(v) >= 4}

print(f"Total bursts: {len(bursts)}")
print(f"Unique (window, data) patterns: {len(pattern_groups)}")
print(f"Candidates for dedup (>= 4 identical): {len(dedup_candidates)}")
total_savings = sum(
    (len(blocks) - 1) * (blocks[0]['count'] + 2)  # vals lines + struct/close lines
    for blocks in dedup_candidates.values()
)
print(f"Estimated lines saved: {total_savings}")

# Analyze each candidate group
for (window, vals), blocks in sorted(dedup_candidates.items(),
                                      key=lambda x: -len(x[1])):
    offsets = [int(b['start_off'], 16) for b in blocks]
    offsets.sort()
    strides = set(offsets[i+1] - offsets[i] for i in range(len(offsets)-1))
    print(f"\n  {window}: {len(blocks)} identical blocks, {blocks[0]['count']} regs each")
    print(f"    Offsets: {', '.join(hex(o) for o in offsets[:5])}...")
    print(f"    Stride(s): {sorted(strides)}")
    print(f"    Sample vals: {list(blocks[0]['vals'])[:4]}...")
    print(f"    IDs: {[b['id'] for b in blocks[:5]]}...")

    # Generate C init function for this group
    func_name = f"zx_{window.replace('/','_').lower()}_pattern_{len(blocks)}x{blocks[0]['count']}"
    print(f"    → would generate: {func_name}()")


# Now generate the C code and modified burst file
print("\n\n=== Generating zx-eth-init-gen.c ===")
init_lines = [
    '// SPDX-License-Identifier: GPL-2.0',
    '/* Auto-generated register init functions — replaces opaque bursts */',
    '',
]

for (window, vals), blocks in sorted(dedup_candidates.items(),
                                      key=lambda x: -len(x[1])):
    offsets = sorted(int(b['start_off'], 16) for b in blocks)
    stride = offsets[1] - offsets[0]
    count = blocks[0]['count']

    # Check all strides are uniform
    if len(set(offsets[i+1]-offsets[i] for i in range(len(offsets)-1))) != 1:
        print(f"  WARNING: non-uniform strides in {window}, skipping")
        continue

    short = window.split('/')[0].lower()
    func_name = f"zx_{short}_init_pattern_{len(blocks)}x{count}"

    init_lines.append(f'static void {func_name}(struct zx_eth *e)')
    init_lines.append('{')
    init_lines.append(f'\tstatic const u32 pattern[{count}] = {{')
    # Format values nicely: 8 per line
    vlist = list(blocks[0]['vals'])
    for i in range(0, len(vlist), 8):
        line_vals = ', '.join(vlist[i:i+8])
        init_lines.append(f'\t\t{line_vals},')
    init_lines.append('\t};')
    init_lines.append(f'\tconst int num_blocks = {len(blocks)};')
    init_lines.append(f'\tconst u32 base_off = {hex(offsets[0])};')
    init_lines.append(f'\tvoid __iomem *win = e->{get_window_field(window)};')
    init_lines.append('')
    init_lines.append('\tfor (int i = 0; i < num_blocks; i++) {')
    init_lines.append(f'\t\tu32 off = base_off + i * {stride};')
    init_lines.append('\t\tfor (int j = 0; j < ARRAY_SIZE(pattern); j++)')
    init_lines.append('\t\t\twritel(pattern[j], win + off + j * 4);')
    init_lines.append('\t}')
    init_lines.append('}')
    init_lines.append('')

    print(f"  Generated: {func_name} ({len(blocks)} blocks × {count} regs)")

Path(OUT_INIT).write_text('\n'.join(init_lines) + '\n')
print(f"\nWritten: {OUT_INIT} ({len(init_lines)} lines)")


def get_window_field(win_name):
    """Map window name to struct zx_eth field."""
    w = win_name.split('/')[0].lower()
    if w in ('pon_tail',):
        return 'pon_early'
    if w in ('npp', 'pp_fuc', 'tm'):
        return 'base'
    if w in ('pon_early',):
        return 'pon_early'
    return 'base'  # default
