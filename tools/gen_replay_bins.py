#!/usr/bin/env python3
"""Generate binary replay files from the autogen .h headers.

Three outputs in initramfs/lib/firmware/zx-replay/:
  stock.bin: [s32 off][u32 val]  records (8B × N)
  cla.bin:   [u32 ram_id][u32 ram_addr][17×u32 data] records (76B × N)
  pm.bin:    [u32 ram_id][u32 ram_addr][8×u32 data]  records (40B × N)

Header has a magic+count prefix:
  uint32 MAGIC = 0x5A584752 ('ZXGR')
  uint32 record_count
"""
import re, struct, sys, os

ROOT = "/home/ubuntu/Projects/MYSELF/ZTE/zxic"
HDR  = ROOT + "/linux-v6.6/drivers/net/ethernet/zte"
# Post-reorg location (2026-05-22): initramfs lives inside the task folder.
OUT  = ROOT + "/tasks/00.01.eth-driver/initramfs/lib/firmware/zx-replay"
MAGIC = 0x5A584752

os.makedirs(OUT, exist_ok=True)

def parse_stock():
    """Lines like '{ -1835008, 0xFFFFFFFF },'"""
    text = open(f"{HDR}/zx279128-eth-stock-regs.h").read()
    pat = re.compile(r"\{\s*(-?0x[0-9a-fA-F]+|-?\d+)\s*,\s*(0x[0-9a-fA-F]+|\d+)\s*\}", re.M)
    entries = []
    for m in pat.finditer(text):
        off = int(m.group(1), 0)
        val = int(m.group(2), 0)
        entries.append((off, val))
    return entries

def parse_cla():
    """Lines like '{ 1, 0x0, { 0x00000001, ... } },'  (17 data words)"""
    text = open(f"{HDR}/zx279128-eth-cla-regs.h").read()
    pat = re.compile(r"\{\s*(\d+)\s*,\s*(0x[0-9a-fA-F]+|\d+)\s*,\s*\{([^}]*)\}\s*\}", re.M)
    entries = []
    for m in pat.finditer(text):
        ram = int(m.group(1))
        addr = int(m.group(2), 0)
        data_str = m.group(3)
        data = [int(x.strip(), 0) for x in data_str.split(",") if x.strip()]
        if len(data) != 17:
            continue
        entries.append((ram, addr, data))
    return entries

def parse_pm():
    """Same as cla but 8 data words"""
    text = open(f"{HDR}/zx279128-eth-pm-regs.h").read()
    pat = re.compile(r"\{\s*(\d+)\s*,\s*(\d+)\s*,\s*\{([^}]*)\}\s*\}", re.M)
    entries = []
    for m in pat.finditer(text):
        ram = int(m.group(1))
        addr = int(m.group(2), 0)
        data_str = m.group(3)
        data = [int(x.strip(), 0) for x in data_str.split(",") if x.strip()]
        if len(data) != 8:
            continue
        entries.append((ram, addr, data))
    return entries

def write_stock(entries):
    path = f"{OUT}/stock.bin"
    with open(path, "wb") as f:
        f.write(struct.pack("<II", MAGIC, len(entries)))
        for off, val in entries:
            f.write(struct.pack("<iI", off, val))
    print(f"  stock.bin: {len(entries)} entries, {os.path.getsize(path)} bytes")

def write_cla(entries):
    path = f"{OUT}/cla.bin"
    with open(path, "wb") as f:
        f.write(struct.pack("<II", MAGIC, len(entries)))
        for ram, addr, data in entries:
            f.write(struct.pack("<II", ram, addr))
            f.write(struct.pack("<17I", *data))
    print(f"  cla.bin:   {len(entries)} entries, {os.path.getsize(path)} bytes")

def write_pm(entries):
    path = f"{OUT}/pm.bin"
    with open(path, "wb") as f:
        f.write(struct.pack("<II", MAGIC, len(entries)))
        for ram, addr, data in entries:
            f.write(struct.pack("<II", ram, addr))
            f.write(struct.pack("<8I", *data))
    print(f"  pm.bin:    {len(entries)} entries, {os.path.getsize(path)} bytes")

if __name__ == "__main__":
    print("Parsing stock regs...")
    s = parse_stock(); print(f"  found {len(s)}")
    print("Parsing CLA...")
    c = parse_cla(); print(f"  found {len(c)}")
    print("Parsing pp_pm...")
    p = parse_pm(); print(f"  found {len(p)}")
    print(f"\nWriting to {OUT}:")
    write_stock(s)
    write_cla(c)
    write_pm(p)
    print("\nDone.")
