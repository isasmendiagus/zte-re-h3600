# -*- coding: utf-8 -*-
# Find functions that reference "setup versioninfo tag" and "Starting kernel"
# Then dump their decompilations.
# @category ZXIC
# @runtime Jython

import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions

KEYWORDS = [
    "setup versioninfo tag",
    "versioninfo",
    "Starting kernel",
    "FDT creation failed",
]

args = getScriptArgs()
out_dir = args[0] if args else "/home/ubuntu/Projects/MYSELF/ZTE/zxic/ghidra/output_uboot"
try: os.makedirs(out_dir)
except OSError: pass
print("output -> " + out_dir)

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

mem = currentProgram.getMemory()
fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
ref_mgr = currentProgram.getReferenceManager()

def safe(s): return re.sub(r'[^a-zA-Z0-9._-]', '_', s)[:80]

# Iterate all defined data and find string matches
found_addrs = []
data_iter = listing.getDefinedData(True)
while data_iter.hasNext():
    d = data_iter.next()
    if d.hasStringValue():
        sv = str(d.getValue())
        for kw in KEYWORDS:
            if kw in sv:
                found_addrs.append((d.getAddress(), sv[:80]))
                break

# Also try just searching memory bytes for the strings (in case Ghidra didn't define them)
from jarray import array as jarray
for kw in KEYWORDS:
    # Jython 2.7 compatible - encode as bytes
    pattern_bytes = jarray([ord(c) for c in kw], 'b')
    addr = currentProgram.getMinAddress()
    end_addr = currentProgram.getMaxAddress()
    found = mem.findBytes(addr, end_addr, pattern_bytes, None, True, monitor)
    while found is not None:
        found_addrs.append((found, kw))
        found = mem.findBytes(found.add(1), end_addr, pattern_bytes, None, True, monitor)

# dedup
seen = set()
unique = []
for a, s in found_addrs:
    k = str(a)
    if k not in seen:
        seen.add(k)
        unique.append((a, s))

print("Unique string addresses: %d" % len(unique))
for addr, sv in unique:
    print("  0x%s: %s" % (addr, sv))
    refs = ref_mgr.getReferencesTo(addr)
    funcs_to_dump = set()
    for r in refs:
        f = fm.getFunctionContaining(r.getFromAddress())
        if f:
            funcs_to_dump.add(f.getEntryPoint())
            print("    refed by func %s @ 0x%s" % (f.getName(), f.getEntryPoint()))
    for entry in funcs_to_dump:
        f = fm.getFunctionAt(entry)
        if not f: continue
        dr = decomp.decompileFunction(f, 60, monitor)
        if dr and dr.decompileCompleted():
            tag = safe(sv[:30])
            path = os.path.join(out_dir, "uboot_%s_%s.c" % (tag, str(f.getName())))
            with open(path, "w") as o:
                o.write("// uses string: %s\n" % sv)
                o.write("// function: %s @ 0x%s\n//\n" % (f.getName(), entry))
                o.write(dr.getDecompiledFunction().getC())
            print("    dumped to %s" % path)

decomp.closeProgram()
print("DONE")
