# -*- coding: utf-8 -*-
# Extract driver functions by tracing references to peripheral physical
# addresses from the extracted DTS. Each LDR rN, =0xAABBCCDD inside a function
# means that function manipulates peripheral 0xAABBCCDD.
#
# @category ZXIC
# @runtime Jython

import os
import re
import struct
from jarray import zeros
from ghidra.app.decompiler import DecompInterface, DecompileOptions

# (label, phys_addr, size_hint) — from /home/ubuntu/Projects/MYSELF/ZTE/firmware/extracted.dts
PERIPHS = [
    ("gic",       0x00801000),
    ("timer_a9", 0x00800200),
    ("twd_wdt",  0x00800620),
    ("mg_crm",   0x00804000),
    ("l2_pl310", 0x00c00000),
    ("iram",     0x00200800),
    ("nand_data",0x00d80000),
    ("nand_reg", 0x00d00000),
    ("mmc_sd",   0x08980000),
    ("usb2_dwc2",0x09000000),
    ("usb3_dwc3",0x09100000),
    ("pcie",     0x10000000),
    ("topcrm",   0x94000000),
    ("temp_sens",0x94100034),
    ("lsp0crpm", 0x94400000),
    ("uart0",    0x94404000),
    ("uart1",    0x94405000),
    ("spifc",    0x94406000),
    ("lsp1crpm", 0x9a100000),
    ("mdio",     0x9a101000),
    ("i2c0",     0x9a102000),
    ("i2c1",     0x9a103000),
    ("ssp",      0x9a105000),
    ("tdm",      0x9a106000),
    ("gephy0",   0x9b000000),
    ("gephy1",   0x9b100000),
    ("gephy2",   0x9b200000),
    ("gephy3",   0x9b300000),
    ("pon",      0x92000000),
    ("tm",       0x92340000),
    ("pp",       0x92380000),
    ("npp",      0x921c0000),
    ("idm",      0x921c8000),
]

DECOMPILE_TIMEOUT = 90

args = getScriptArgs()
out_dir = args[0] if len(args) >= 1 else "/home/ubuntu/Projects/MYSELF/ZTE/ghidra/output_drivers"
try:
    os.makedirs(out_dir)
except OSError:
    pass
print("output -> " + out_dir)

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

mem = currentProgram.getMemory()
func_mgr = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
addr_factory = currentProgram.getAddressFactory()
addr_space = addr_factory.getDefaultAddressSpace()

# Build sorted list of function entry points for fast nearest-before lookup.
all_funcs = sorted(func_mgr.getFunctions(True), key=lambda f: f.getEntryPoint().getOffset())
all_func_offsets = [f.getEntryPoint().getOffset() for f in all_funcs]
import bisect
def func_before(addr_int):
    """Return the Function whose entry is the largest <= addr_int."""
    idx = bisect.bisect_right(all_func_offsets, addr_int) - 1
    if idx < 0:
        return None
    return all_funcs[idx]
print("indexed {0} functions for nearest-before lookup".format(len(all_funcs)))

# Read all memory blocks
mem_dump = []
blocks = [b for b in mem.getBlocks() if b.isInitialized() and b.isLoaded()]
for b in blocks:
    sz = int(b.getSize())
    if sz > 64*1024*1024: continue
    jbarr = zeros(sz, 'b')
    try:
        mem.getBytes(b.getStart(), jbarr)
    except Exception as e:
        continue
    data_str = "".join(chr(x & 0xff) for x in jbarr)
    mem_dump.append((b.getStart().getOffset(), data_str))
print("loaded {0} memory blocks".format(len(mem_dump)))

def find_le32_refs(target_addr):
    needle = struct.pack("<I", target_addr & 0xffffffff)
    results = []
    for base, data in mem_dump:
        i = 0
        while True:
            j = data.find(needle, i)
            if j < 0: break
            if j % 4 == 0:
                results.append(base + j)
            i = j + 1
    return results

dumped = set()
index_lines = [
    "# Driver-function index by peripheral",
    "",
    "Each peripheral physical address from extracted.dts is searched as a 32-bit",
    "LE constant in code. Functions containing such loads are decompiled.",
    "",
    "| Periph | Phys addr | LE32 hits | Functions extracted |",
    "|---|---|---|---|",
]

def safe(s):
    return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:80]

for label, paddr in PERIPHS:
    if monitor.isCancelled(): break
    refs = find_le32_refs(paddr)
    extracted = []
    for ref in refs:
        if len(extracted) >= 6: break
        ref_obj = addr_space.getAddress(ref)
        f = func_mgr.getFunctionContaining(ref_obj)
        if f is None:
            # Literal pool is between funcs. Find the function before this addr;
            # only accept it if the gap is small (literal pool is right after func body).
            f = func_before(ref)
            if f is None:
                continue
            gap = ref - f.getBody().getMaxAddress().getOffset()
            if gap > 4096:
                continue
        key = f.getEntryPoint().getOffset()
        if key in dumped:
            extracted.append("{0}__dup".format(f.getName()))
            continue
        dumped.add(key)
        dr = decomp.decompileFunction(f, DECOMPILE_TIMEOUT, monitor)
        if dr is None or not dr.decompileCompleted():
            extracted.append("{0}__decompfail".format(f.getName()))
            continue
        c_code = dr.getDecompiledFunction().getC()
        fname = "{0}__{1}__{2}.c".format(
            label, "0x{0:08x}".format(paddr), safe(str(f.getName())))
        path = os.path.join(out_dir, fname)
        out = open(path, "w")
        out.write("// peripheral: {0} (0x{1:08x})\n".format(label, paddr))
        out.write("// LE32 ref at 0x{0:x}\n".format(ref))
        out.write("// function: {0} @ 0x{1:x}\n".format(f.getName(), key))
        out.write("// total LE32 refs to this addr: {0}\n".format(len(refs)))
        out.write("//\n")
        out.write(c_code)
        out.close()
        extracted.append(str(f.getName()))
    line = "| {0} | 0x{1:08x} | {2} | {3} |".format(
        label, paddr, len(refs),
        ", ".join(extracted) if extracted else "(no func found)")
    index_lines.append(line)
    print(line)

f = open(os.path.join(out_dir, "INDEX.md"), "w")
f.write("\n".join(index_lines))
f.write("\n")
f.close()

decomp.closeProgram()
print("DONE: {0} unique driver functions extracted".format(len(dumped)))
