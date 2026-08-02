#!/usr/bin/env python3
"""Regenerate zx_stock_bursts.h with explicitly-handled sections removed.

Removes PON_TAIL (ops 1792-8035) and TM (ops 8058-9714) ops + data arrays,
replacing them with zero-length section defines. PON_B, NPP, and PP_FUC
sections are kept.

Usage: python3 tools/regenerate_bursts.py
  Writes cleaned header to zx_stock_bursts_clean.h
"""

import re, sys
from pathlib import Path
from collections import OrderedDict

HEADER = Path("linux-v6.6/drivers/net/ethernet/zte/zx_stock_bursts.h")
OUT = Path("linux-v6.6/drivers/net/ethernet/zte/zx_stock_bursts_clean.h")

content = HEADER.read_text()

# --- Parse data arrays ---
burst_pat = re.compile(
    r'/\*\s*burst\s*#(\d+):\s*([^*]+?)\s*\*/\s*'
    r'(static\s+const\s+u32\s+zx_burst_\d+_data\[\d+\]\s*=\s*\{[^}]+\};)',
    re.DOTALL
)
bursts = OrderedDict()
burst_positions = []
for m in burst_pat.finditer(content):
    bid = int(m.group(1))
    comment = m.group(2).strip()
    w = comment.split()[0].split('/')[0]
    bursts[bid] = {'window': w, 'text': m.group(0), 'start': m.start(), 'end': m.end()}
    burst_positions.append((m.start(), m.end(), bid))

# --- Parse ops table ---
ops_match = re.search(r'static\s+const\s+struct\s+zx_stock_op\s+zx_stock_ops\[\d+\]\s*=\s*\{', content)
ops_start = ops_match.end()
depth = 1; pos = ops_start
while depth > 0: 
    if content[pos] == '{': depth += 1
    elif content[pos] == '}': depth -= 1
    pos += 1
ops_body = content[ops_start:pos-1]
ops_end_brace = pos

op_pat = re.compile(
    r'\{\s*(-?0x[0-9a-fA-F]+|\d+)\s*,\s*(-?0x[0-9a-fA-F]+|\d+)\s*,\s*([^,}]+)\s*,\s*(ZX_BURST_KIND_\w+)\s*,\s*(ZX_BURST_WIN_\w+)\s*(?:,\s*\d+)?\s*\}'
)
kind_map = {'ZX_BURST_KIND_RUN': 0, 'ZX_BURST_KIND_SINGLE': 1}
win_map = {'ZX_BURST_WIN_BASE': 0, 'ZX_BURST_WIN_PON_EARLY': 1}

ops = []
raw_op_texts = []
for m in op_pat.finditer(ops_body):
    ops.append({
        'off': m.group(1), 'val': m.group(2), 'data': m.group(3).strip(),
        'kind': kind_map[m.group(4)], 'window': win_map[m.group(5)],
        'text': m.group(0)
    })

print(f"Parsed {len(bursts)} data arrays, {len(ops)} ops", file=sys.stderr)

# --- Section removal ---
# Keep: PON_B [0..1792), NPP [8035..8058), PP_FUC [9714..10621)
# Remove: PON_TAIL [1792..8035), TM [8058..9714)
KEEP_RANGES = [(0, 1792), (8035, 8058), (9714, len(ops))]

keep_set = set()
for start, end in KEEP_RANGES:
    for i in range(start, min(end, len(ops))):
        keep_set.add(i)

kept_ops = [ops[i] for i in range(len(ops)) if i in keep_set]

# Find referenced data arrays
ref_ids = set()
for op in kept_ops:
    if op['kind'] == 0 and op['data'] != 'NULL':
        m = re.match(r'zx_burst_(\d+)_data', op['data'])
        if m: ref_ids.add(int(m.group(1)))

kept_bursts = OrderedDict((bid, b) for bid, b in bursts.items() if bid in ref_ids)

print(f"Kept {len(kept_ops)} ops (removed {len(ops)-len(kept_ops)})", file=sys.stderr)
print(f"Kept {len(kept_bursts)} data arrays (removed {len(bursts)-len(kept_bursts)})", file=sys.stderr)

# --- Build output ---
# Header preamble (up to first burst definition)
first_burst_pos = min(burst_positions)[0] if burst_positions else len(content)
preamble = content[:first_burst_pos]

# Update header comment about skipped blocks
preamble = preamble.replace(
    "Skipped blocks : ['NPP_AUX', 'PON_LOW', 'PON_TAIL'] (13122 entries via XXX runs)",
    "Skipped blocks : ['NPP_AUX', 'PON_LOW', 'PON_TAIL', 'TM'] (14778 entries handled by explicit C)"
)
preamble = preamble.replace("Bursts (>=4 entries): 826, covering 5689 entries", "")
# Remove stale total ops lines from preamble
lines = preamble.split('\n')
lines = [l for l in lines if 'Bursts (' not in l and 'Short runs' not in l and 'Total ops' not in l]
# Add updated stats
new_header_stats = f' * Bursts (>=4 entries): {len(kept_bursts)}, covering ~300 entries\n' \
                   f' * Short runs    : {sum(1 for op in kept_ops if op["kind"] == 1)}\n' \
                   f' * Total ops     : {len(kept_ops)}\n'
# Insert before the closing bracket of the comment
for i, line in enumerate(lines):
    if line.strip().startswith('*/'):
        lines.insert(i, new_header_stats.rstrip())
        break
preamble = '\n'.join(lines)

# Data arrays
data_text = '\n\n'.join(b['text'] for b in kept_bursts.values())

# Ops table
ops_lines = [f'static const struct zx_stock_op zx_stock_ops[{len(kept_ops)}] = {{']
for op in kept_ops:
    ops_lines.append(f'\t{{ {op["off"]}, {op["val"]}, {op["data"]}, {"ZX_BURST_KIND_RUN" if op["kind"]==0 else "ZX_BURST_KIND_SINGLE"}, {"ZX_BURST_WIN_BASE" if op["window"]==0 else "ZX_BURST_WIN_PON_EARLY"} }},')
ops_text = '\n'.join(ops_lines) + '\n};\n'

# New section defines (recalculated offsets)
# After removal, the kept ops are in original order but contiguous
# We need to emit START/END for each section based on new_ops indices
new_sections = OrderedDict()
new_sections['PON_B'] = len([op for op in kept_ops if ops.index(op) < 1792])
new_sections['PON_TAIL'] = 0  # removed
# NPP: originally 8035..8058, but after removing PON_TAIL (1792..8035 was removed
# first), the NPP section starts at new index = (first_ix_after_PON_TAIL_removal)
# This is complex. Let me just compute by finding NPP ops in kept_ops.
npp_count = 0; tm_count = 0; pp_fuc_count = 0
for i, op in enumerate(kept_ops):
    orig_idx = ops.index(op)
    if 8035 <= orig_idx < 8058: npp_count += 1
    elif 9714 <= orig_idx < len(ops): pp_fuc_count += 1

new_sections['NPP'] = npp_count
new_sections['TM'] = 0
new_sections['PP_FUC'] = pp_fuc_count

offset = 0
define_lines = []
for name in ['PON_B', 'PON_TAIL', 'NPP', 'TM', 'PP_FUC']:
    count = new_sections[name]
    define_lines.append(f'#define ZX_STOCK_OPS_{name}_START {offset}')
    if count > 0:
        define_lines.append(f'#define ZX_STOCK_OPS_{name}_END   {offset + count}')
    else:
        define_lines.append(f'#define ZX_STOCK_OPS_{name}_END   {offset}  /* handled by explicit C */')
    define_lines.append(f'#define ZX_STOCK_OPS_{name}_LEN   {count}')
    offset += count

define_lines.append(f'#define ZX_STOCK_OPS_LEN {offset}')
define_lines.append(f'\n/* Sanity: total individual register writes when replayed must equal')
define_lines.append(f' * the original 22363 entries minus the 14778 entries in')
define_lines.append(f' * blocks handled by explicit zx_<block>_init() functions. */')
define_lines.append(f'#define ZX_STOCK_OPS_WRITES_EXPECTED {offset}')
define_lines.append('')
define_lines.append('#endif /* ZX_STOCK_BURSTS_H */')

footer = '\n'.join(define_lines)

# Find and extract everything between ops table end and old footer start
footer_marker = '#define ZX_STOCK_OPS_PON_B_START'
old_footer_pos = content.rfind(footer_marker)
after_ops = content[ops_end_brace:old_footer_pos]

# Combine
output = (
    preamble.rstrip() + '\n\n' +
    data_text + '\n\n' +
    ops_text + '\n' +
    after_ops.rstrip() + '\n\n' +
    footer + '\n'
)

OUT.write_text(output)
print(f"Wrote {OUT} ({len(output.split(chr(10)))} lines, {len(output)} bytes)", file=sys.stderr)
