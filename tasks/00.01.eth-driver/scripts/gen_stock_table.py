#!/usr/bin/env python3
"""Generate linux-v6.6/.../zx_stock_table.h from stock.bin.

Each stock.bin entry is `struct { s32 off; u32 val; }` (8 bytes).
22,363 entries captured from stock device's MMIO at boot. Negative
offsets go to pon_early; non-negative go to base.

This is the BIG one (179 KB blob). For now we just embed as static
const table — same writes, no semantic change. Future refactors will
split into per-block init functions (chip_tm_init, pp_init, etc.) using
the stockport call-graph + Ghidra decomp.

File format: [u32 magic 'ZXGR' = 0x5A584752][u32 count][records × 8 bytes]

Run from repo root.
"""
import struct
from pathlib import Path

SRC = Path("tasks/00.01.eth-driver/initramfs/lib/firmware/zx-replay/stock.bin")
DST = Path("linux-v6.6/drivers/net/ethernet/zte/zx_stock_table.h")

HDR_SZ = 8
ENTRY_SZ = 8
EXPECTED_MAGIC = 0x5A584752


def main():
    data = SRC.read_bytes()
    magic, count = struct.unpack_from("<II", data, 0)
    if magic != EXPECTED_MAGIC:
        raise SystemExit(f"bad magic 0x{magic:08x}")
    n = (len(data) - HDR_SZ) // ENTRY_SZ
    if n != count:
        raise SystemExit(f"count mismatch: {count} vs {n}")

    out = []
    out.append("/* zx_stock_table.h — auto-generated from stock.bin by")
    out.append(" *   tasks/00.01.eth-driver/scripts/gen_stock_table.py")
    out.append(" *")
    out.append(" * Replaces firmware_request(\"zx-replay/stock.bin\") with a static C array.")
    out.append(f" * {n} entries × {ENTRY_SZ} bytes = {n*ENTRY_SZ} bytes (~{n*ENTRY_SZ//1024} KB .rodata).")
    out.append(" *")
    out.append(" * Future refactor: split into per-block explicit init functions")
    out.append(" * (chip_tm_init, pp_init, npp_init, idm_init, etc.) using stockport")
    out.append(" * call-graph + Ghidra decomp of stock kmods.")
    out.append(" *")
    out.append(" * Regenerate after re-capturing stock.bin:")
    out.append(" *   python3 tasks/00.01.eth-driver/scripts/gen_stock_table.py")
    out.append(" */")
    out.append("#ifndef ZX_STOCK_TABLE_H")
    out.append("#define ZX_STOCK_TABLE_H")
    out.append("")
    out.append("#include <linux/types.h>")
    out.append("")
    out.append("struct zx_stock_entry { s32 off; u32 val; } __packed;")
    out.append("")
    out.append(f"static const struct zx_stock_entry zx_stock_init_table[{n}] = {{")
    # Group entries 8 per line for readability
    for i in range(0, n, 8):
        chunk = []
        for j in range(min(8, n - i)):
            off = HDR_SZ + (i + j) * ENTRY_SZ
            off_val, val = struct.unpack_from("<iI", data, off)
            chunk.append(f"{{{off_val:#11x}, {val:#010x}}}")
        out.append(f"\t/*{i:5d}*/ " + ", ".join(chunk) + ",")
    out.append("};")
    out.append("")
    out.append(f"#define ZX_STOCK_INIT_TABLE_LEN {n}")
    out.append("")
    out.append("#endif /* ZX_STOCK_TABLE_H */")
    DST.write_text("\n".join(out) + "\n")
    print(f"wrote {DST} ({n} entries, {DST.stat().st_size} bytes)")


if __name__ == "__main__":
    main()
