# -*- coding: utf-8 -*-
# Find functions that reference the AES T-tables in vmlinux.
# T-table addresses (extracted via binwalk + struct check):
#   Te0 (forward) starts at 0xc04b8de8 (Te0[0] = 0xc66363a5)
#   Te4 (forward) starts at 0xc04b75e8 (Te4[0] = 0x63636363)
# A function that loads ANY of these addresses is the AES core.
# Functions that call THAT are the higher-level encrypt/decrypt setup.
#
# @category ZXIC
# @runtime Jython

import os, struct, re
from jarray import zeros
from ghidra.app.decompiler import DecompInterface, DecompileOptions

TARGETS = [
    ("Te0",  0xc04b8de8),
    ("Te4",  0xc04b75e8),
    # Inverse tables — would be ~256B before forward (typical layout)
    ("Td0?", 0xc04ade60),
    ("Td0?", 0xc04ad000),
]
DECOMPILE_TIMEOUT = 60

args = getScriptArgs()
out_dir = args[0] if args else "/home/ubuntu/Projects/MYSELF/ZTE/H3600/ghidra/output_aes"
try: os.makedirs(out_dir)
except OSError: pass
print("output -> " + out_dir)

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

mem = currentProgram.getMemory()
fm = currentProgram.getFunctionManager()
sp = currentProgram.getAddressFactory().getDefaultAddressSpace()
import bisect
all_funcs = sorted(fm.getFunctions(True), key=lambda f: f.getEntryPoint().getOffset())
all_off = [f.getEntryPoint().getOffset() for f in all_funcs]

# Read all memory
mem_data = []
for b in mem.getBlocks():
    if not b.isInitialized() or not b.isLoaded(): continue
    sz = int(b.getSize())
    if sz > 64*1024*1024: continue
    a = zeros(sz, 'b')
    try: mem.getBytes(b.getStart(), a)
    except: continue
    s = "".join(chr(x & 0xff) for x in a)
    mem_data.append((b.getStart().getOffset(), s))

def find_le32(target):
    needle = struct.pack("<I", target & 0xffffffff)
    out = []
    for base, data in mem_data:
        i = 0
        while True:
            j = data.find(needle, i)
            if j < 0: break
            if j % 4 == 0: out.append(base + j)
            i = j + 1
    return out

def func_at_or_before(addr):
    aobj = sp.getAddress(addr & 0xfffffffe)
    f = fm.getFunctionContaining(aobj)
    if f: return f
    idx = bisect.bisect_right(all_off, addr) - 1
    if idx >= 0:
        cand = all_funcs[idx]
        if addr - cand.getBody().getMaxAddress().getOffset() < 0x4000:
            return cand
    return None

aes_funcs = set()
print("\n=== xrefs to AES T-tables ===")
for name, addr in TARGETS:
    refs = find_le32(addr)
    print("  {0} @ 0x{1:x}: {2} refs".format(name, addr, len(refs)))
    for r in refs[:5]:
        f = func_at_or_before(r)
        if f:
            entry = f.getEntryPoint().getOffset()
            print("    ref @ 0x{0:x} -> func {1} @ 0x{2:x}".format(r, f.getName(), entry))
            aes_funcs.add(entry)

print("\n=== {0} unique AES core functions found ===".format(len(aes_funcs)))

# Decompile each AES core, then find their callers
def safe(s): return re.sub(r'[^a-zA-Z0-9._-]', '_', s)[:80]

caller_funcs = set()
for entry in aes_funcs:
    f = fm.getFunctionAt(sp.getAddress(entry))
    if not f: continue
    print("Decompiling {0} @ 0x{1:x}".format(f.getName(), entry))
    dr = decomp.decompileFunction(f, DECOMPILE_TIMEOUT, monitor)
    if dr and dr.decompileCompleted():
        path = os.path.join(out_dir, "aes_core__{0}.c".format(safe(str(f.getName()))))
        with open(path, "w") as o:
            o.write("// AES core (uses T-tables) @ 0x{0:x}\n//\n".format(entry))
            o.write(dr.getDecompiledFunction().getC())
    # Find callers
    callers = f.getCallingFunctions(monitor)
    for c in callers:
        caller_funcs.add(c.getEntryPoint().getOffset())
    print("  callers: {0}".format(len(callers)))

print("\n=== Decompile {0} callers ===".format(len(caller_funcs)))
for entry in caller_funcs:
    f = fm.getFunctionAt(sp.getAddress(entry))
    if not f: continue
    dr = decomp.decompileFunction(f, DECOMPILE_TIMEOUT, monitor)
    if dr and dr.decompileCompleted():
        path = os.path.join(out_dir, "caller__{0}.c".format(safe(str(f.getName()))))
        with open(path, "w") as o:
            o.write("// Caller of AES core @ 0x{0:x}\n//\n".format(entry))
            o.write(dr.getDecompiledFunction().getC())

decomp.closeProgram()
print("\nDONE")
