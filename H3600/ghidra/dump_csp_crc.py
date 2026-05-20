# -*- coding: utf-8 -*-
# Find and dump csp_crc function from U-Boot
# @category ZXIC
# @runtime Jython
import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions
from ghidra.program.model.data import StringDataType

args = getScriptArgs()
out_dir = args[0] if args else "/tmp/csp_crc"
try: os.makedirs(out_dir)
except OSError: pass

mem = currentProgram.getMemory()
af = currentProgram.getAddressFactory()
listing = currentProgram.getListing()
ref_mgr = currentProgram.getReferenceManager()
func_mgr = currentProgram.getFunctionManager()

blocks = mem.getBlocks()
base = blocks[0].getStart().getOffset() if blocks else 0
print("base = 0x%x" % base)

# Find file offsets of csp_crc related strings
# We saw "csp_crc:103  >>csp_crc,  data addr:%x, crc_len:%x" pattern
data = open("/home/ubuntu/Projects/MYSELF/ZTE/H3600/partitions/01_bootloader.bin", "rb").read()
needle = b"csp_crc:"
positions = []
pos = 0
while True:
    i = data.find(needle, pos)
    if i < 0: break
    positions.append(i)
    pos = i + 1
print("csp_crc string at file offsets: " + str([hex(p) for p in positions]))

# create strings at those positions and find xrefs
for off in positions:
    addr = af.getAddress("%x" % (base + off))
    try:
        if listing.getDataAt(addr) is None:
            listing.createData(addr, StringDataType.dataType, 80)
    except: pass
    refs = ref_mgr.getReferencesTo(addr)
    print("xrefs to '%s' @ 0x%x: %d" % (data[off:off+30].decode(errors='replace'), base+off, len(list(refs))))
    for r in ref_mgr.getReferencesTo(addr):
        f = func_mgr.getFunctionContaining(r.getFromAddress())
        if f:
            print("  from func at 0x%x" % f.getEntryPoint().getOffset())

# Also try to find function "csp_crc" directly by name
print("\nAll funcs in 0x47f00000-0x47f80000 (likely csp_crc area):")
decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

def safe(s): return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:80]

# Look at functions in this range that are small (CRC funcs are usually 50-200 bytes)
for f in func_mgr.getFunctions(True):
    e = f.getEntryPoint().getOffset()
    if not (0x47f00000 <= e <= 0x47f80000): continue
    sz = f.getBody().getNumAddresses()
    if 50 <= sz <= 500:
        # Dump it
        dr = decomp.decompileFunction(f, 30, monitor)
        if dr and dr.decompileCompleted():
            with open(os.path.join(out_dir, "FUN_%x.c" % e), "w") as fp:
                fp.write("// FUN_%x size=%d\n" % (e, sz))
                fp.write(dr.getDecompiledFunction().getC())
decomp.closeProgram()
print("done")
