# -*- coding: utf-8 -*-
# Locate function entries via the kallsyms / __ksymtab tables.
# The Linux kernel exports symbols via __ksymtab section, with entries:
#   struct kernel_symbol { unsigned long value; const char *name; };
# So for each interesting symbol name, we find the LE32 ref to that string
# (which is the .name field of a kernel_symbol entry), then read the .value
# field at offset -4 — that's the function address.
#
# @category ZXIC
# @runtime Jython

import os
import re
import struct
from jarray import zeros
from ghidra.app.decompiler import DecompInterface, DecompileOptions

TARGETS = [
    "zx_mdio_read", "zx_mdio_write",
    "zx_phy_int", "of_iomap",
    "clk_register_fixed_rate", "clk_register_divider",
    "clk_register_mux", "clk_register_gate",
    "platform_get_irq", "devm_kzalloc",
    "request_mem_region", "ioremap",
    "fb_mdio_pclk", "fb_mdio_wclk",
    "denali_init", "dwc3_zx_probe",
    "smac_init", "tm_pon_tm_init",
]
DECOMPILE_TIMEOUT = 60

args = getScriptArgs()
out_dir = args[0] if len(args) >= 1 else "/home/ubuntu/Projects/MYSELF/ZTE/ghidra/output_kallsyms"
try: os.makedirs(out_dir)
except OSError: pass
print("output -> " + out_dir)

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

mem = currentProgram.getMemory()
func_mgr = currentProgram.getFunctionManager()
addr_factory = currentProgram.getAddressFactory()
addr_space = addr_factory.getDefaultAddressSpace()

KMIN = 0xC0008000
KMAX = 0xC0700000
# Code is below ~0xC05E0000, .rodata strings above. For ksymtab.value
# filtering we want code addresses only.
CODE_MAX = 0xC05E0000

# Read entire memory
mem_dump = []
for b in mem.getBlocks():
    if not b.isInitialized() or not b.isLoaded(): continue
    sz = int(b.getSize())
    if sz > 64*1024*1024: continue
    jb = zeros(sz, 'b')
    try: mem.getBytes(b.getStart(), jb)
    except: continue
    mem_dump.append((b.getStart().getOffset(),
                     "".join(chr(x & 0xff) for x in jb)))
print("loaded {0} blocks".format(len(mem_dump)))

def find_string(s):
    nb = s + "\x00"
    out = []
    for base, data in mem_dump:
        i = 0
        while True:
            j = data.find(nb, i)
            if j < 0: break
            if j > 0 and 0x20 <= ord(data[j-1]) <= 0x7e:
                # not a standalone string start; skip
                i = j + 1; continue
            out.append(base + j)
            i = j + 1
    return out

def find_le32_refs(target):
    needle = struct.pack("<I", target & 0xffffffff)
    out = []
    for base, data in mem_dump:
        i = 0
        while True:
            j = data.find(needle, i)
            if j < 0: break
            if j % 4 == 0: out.append(base + j)
            i = j + 1
    return out

def read_le32(off):
    for base, data in mem_dump:
        if base <= off < base + len(data) - 3:
            local = off - base
            return struct.unpack("<I", data[local:local+4])[0]
    return None

import bisect
all_funcs = sorted(func_mgr.getFunctions(True),
                   key=lambda f: f.getEntryPoint().getOffset())
all_func_offsets = [f.getEntryPoint().getOffset() for f in all_funcs]

def func_at_or_before(addr_int):
    aobj = addr_space.getAddress(addr_int & 0xfffffffe)
    f = func_mgr.getFunctionAt(aobj)
    if f is not None: return f
    idx = bisect.bisect_right(all_func_offsets, addr_int) - 1
    if idx >= 0:
        return all_funcs[idx]
    return None

index_lines = ["# kallsyms-based function lookup", "",
               "| Symbol | String addr | Refs | Func addr | Decompiled |",
               "|---|---|---|---|---|"]

for sym in TARGETS:
    print("---", sym, "---")
    str_addrs = find_string(sym)
    if not str_addrs:
        print("  not found")
        index_lines.append("| `{0}` | NOT FOUND | - | - | - |".format(sym))
        continue
    candidates = []  # list of (string_addr, ref_addr, value)
    for sa in str_addrs:
        for r in find_le32_refs(sa):
            # r could be the .name field of __ksymtab entry — read the .value at r-4
            v = read_le32(r - 4)
            if v is not None and KMIN <= v < CODE_MAX:
                candidates.append((sa, r, v))
    if not candidates:
        index_lines.append("| `{0}` | 0x{1:x} | 0 | - | (no ksymtab match) |".format(
            sym, str_addrs[0]))
        continue
    # Pick first plausible
    sa, r, v = candidates[0]
    f = func_at_or_before(v)
    if f is None:
        index_lines.append("| `{0}` | 0x{1:x} | {2} | 0x{3:x} | no func |".format(
            sym, sa, len(candidates), v))
        continue
    dr = decomp.decompileFunction(f, DECOMPILE_TIMEOUT, monitor)
    if dr is None or not dr.decompileCompleted():
        index_lines.append("| `{0}` | 0x{1:x} | {2} | 0x{3:x} | failed |".format(
            sym, sa, len(candidates), v))
        continue
    c_code = dr.getDecompiledFunction().getC()
    fname = sym + ".c"
    out = open(os.path.join(out_dir, fname), "w")
    out.write("// kallsyms symbol: {0}\n".format(sym))
    out.write("// string @ 0x{0:x}, .value @ 0x{1:x} = 0x{2:x}\n".format(
        sa, r-4, v))
    out.write("// Function: {0} @ 0x{1:x}\n".format(
        f.getName(), f.getEntryPoint().getOffset()))
    out.write("//\n")
    out.write(c_code)
    out.close()
    index_lines.append("| `{0}` | 0x{1:x} | {2} | 0x{3:x} | {4} |".format(
        sym, sa, len(candidates), v, f.getName()))

f = open(os.path.join(out_dir, "INDEX.md"), "w")
f.write("\n".join(index_lines)); f.write("\n"); f.close()
decomp.closeProgram()
print("DONE")
