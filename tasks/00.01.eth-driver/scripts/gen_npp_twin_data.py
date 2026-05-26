#!/usr/bin/env python3
"""gen_npp_twin_data.py — refactor #38 Phase 9f

Emits linux-v6.6/.../zx_npp_twin_data.h with three static const arrays
holding the (off, val) writes for each NPP twin-pair sub-block:

  - NPP twin 01: instance 0 + instance 1 (base 0x0 and 0x2000)
  - NPP twin 23: instance 2 + instance 3 (base 0x4000 and 0x6000)
  - NPP twin 67: instance 6 + instance 7 (base 0xc000 and 0xe000)

Each pair was verified BIT-IDENTICAL between its two instances in
stock_init_table[]. The driver writes one shared array twice (once
per instance base), saving roughly half the rodata for these blocks.

Special note on pair 6/7 entries at +0x280..+0x2bc — this is an embedded
Ethernet packet template (dst MAC + IPv4/TCP header) used by some HW
classifier feature. It is environment-specific in the original capture
(includes the host MAC of the unit cspstart booted into). Preserved
bit-for-bit; future work may construct it dynamically.

Run from repo root.
"""
import re
from collections import defaultdict
from pathlib import Path

SRC = Path("linux-v6.6/drivers/net/ethernet/zte/zx_stock_table.h")
DST = Path("linux-v6.6/drivers/net/ethernet/zte/zx_npp_twin_data.h")

STRIDE = 0x2000
PAIRS = [
    ("01", 0, 1),
    ("23", 2, 3),
    ("67", 6, 7),
]


def main():
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

    # Slice to NPP block
    npp = [(o, v) for o, v in entries if 0 <= o < 0x40000]

    # Group by instance, keep per-instance offset→val map
    inst_data = defaultdict(dict)
    for off, val in npp:
        inst = off // STRIDE
        rel = off % STRIDE
        inst_data[inst][rel] = val

    # Verify each pair is bit-identical
    for name, a, b in PAIRS:
        ka = sorted(inst_data[a])
        kb = sorted(inst_data[b])
        assert ka == kb, f"Pair {name}: instance {a} and {b} have different offset sets"
        for o in ka:
            assert inst_data[a][o] == inst_data[b][o], (
                f"Pair {name}: value mismatch at +{o:#x}"
            )

    out = []
    out.append("/* zx_npp_twin_data.h — auto-generated from zx_stock_table.h by")
    out.append(" *   tasks/00.01.eth-driver/scripts/gen_npp_twin_data.py")
    out.append(" *")
    out.append(" * Refactor #38 Phase 9f: NPP twin-pair data extraction.")
    out.append(" * Three pairs of bit-identical sub-block init writes that")
    out.append(" * stock applied to two instances each. We store the writes")
    out.append(" * once and the driver replays them to both instance bases.")
    out.append(" */")
    out.append("#ifndef ZX_NPP_TWIN_DATA_H")
    out.append("#define ZX_NPP_TWIN_DATA_H")
    out.append("")
    out.append("#include <linux/types.h>")
    out.append("")
    out.append("struct zx_off_val { u32 off; u32 val; };")
    out.append("")

    for name, a, b in PAIRS:
        sorted_offs = sorted(inst_data[a])
        out.append(f"/* NPP twin pair {name}: {len(sorted_offs)} writes per instance,")
        out.append(f" * applied to NPP base + 0x{a * STRIDE:04x} (instance {a}) AND")
        out.append(f" * NPP base + 0x{b * STRIDE:04x} (instance {b}). */")
        out.append(f"static const struct zx_off_val zx_npp_pair_{name}[{len(sorted_offs)}] = {{")
        for o in sorted_offs:
            v = inst_data[a][o]
            out.append(f"\t{{ {o:#06x}, {v:#010x} }},")
        out.append("};")
        out.append("")

    out.append("#endif /* ZX_NPP_TWIN_DATA_H */")

    DST.write_text("\n".join(out) + "\n")
    print(f"wrote {DST} ({DST.stat().st_size} bytes)")
    total_writes = sum(len(inst_data[a]) for _, a, _ in PAIRS) * 2
    total_dedup = sum(len(inst_data[a]) for _, a, _ in PAIRS)
    print(f"Pair data: {total_dedup} unique writes, {total_writes} replayed (½ saved)")


if __name__ == "__main__":
    main()
