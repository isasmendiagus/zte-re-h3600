#!/usr/bin/env python3
"""Generate linux-v6.6/.../zx_cla_table.h from cla.bin.

Each cla.bin entry is `struct { u32 ram_id; u32 ram_addr; u32 data[17]; }`
totalling 76 bytes. The .bin is captured from stock device's CLA RAM
contents at boot — we embed it as a const C table so the driver doesn't
need to firmware_request("zx-replay/cla.bin") at runtime. Same writes.

Run from repo root.
"""
import struct
from pathlib import Path

SRC = Path("tasks/00.01.eth-driver/initramfs/lib/firmware/zx-replay/cla.bin")
DST = Path("linux-v6.6/drivers/net/ethernet/zte/zx_cla_table.h")

# File format: [u32 magic 'ZXGR' = 0x5A584752][u32 count][records of 76 bytes]
HDR_SZ = 8
ENTRY_SZ = 76
EXPECTED_MAGIC = 0x5A584752

def main():
    data = SRC.read_bytes()
    magic, count = struct.unpack_from("<II", data, 0)
    if magic != EXPECTED_MAGIC:
        raise SystemExit(f"bad magic 0x{magic:08x} (expected 0x{EXPECTED_MAGIC:08x})")
    n = (len(data) - HDR_SZ) // ENTRY_SZ
    if n != count:
        raise SystemExit(f"count mismatch: header says {count}, file has {n}")
    out = []
    out.append("/* zx_cla_table.h — auto-generated from cla.bin by")
    out.append(" *   tasks/00.01.eth-driver/scripts/gen_cla_table.py")
    out.append(" *")
    out.append(" * Replaces firmware_request(\"zx-replay/cla.bin\") with a static C array.")
    out.append(" * Same bit-exact contents; no semantic change.")
    out.append(f" * {n} entries × {ENTRY_SZ} bytes = {n*ENTRY_SZ} bytes (~{n*ENTRY_SZ//1024} KB .rodata in vmlinux).")
    out.append(" *")
    out.append(" * Regenerate after re-capturing cla.bin:")
    out.append(" *   python3 tasks/00.01.eth-driver/scripts/gen_cla_table.py")
    out.append(" */")
    out.append("#ifndef ZX_CLA_TABLE_H")
    out.append("#define ZX_CLA_TABLE_H")
    out.append("")
    out.append("#include <linux/types.h>")
    out.append("")
    out.append("struct zx_cla_entry { u32 ram_id; u32 ram_addr; u32 data[17]; } __packed;")
    out.append("")
    out.append(f"static const struct zx_cla_entry zx_cla_init_table[{n}] = {{")
    for i in range(n):
        off = HDR_SZ + i * ENTRY_SZ
        fields = struct.unpack_from("<19I", data, off)
        rid, addr = fields[0], fields[1]
        d = fields[2:]
        out.append(f"\t/*{i:4d}*/ {{ {rid:#010x}, {addr:#010x}, {{ " +
                   ", ".join(f"{v:#010x}" for v in d) + " } },")
    out.append("};")
    out.append("")
    out.append(f"#define ZX_CLA_INIT_TABLE_LEN {n}")
    out.append("")
    out.append("#endif /* ZX_CLA_TABLE_H */")
    DST.write_text("\n".join(out) + "\n")
    print(f"wrote {DST} ({n} entries, {DST.stat().st_size} bytes)")

if __name__ == "__main__":
    main()
