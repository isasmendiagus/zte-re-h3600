# -*- coding: utf-8 -*-
# Find functions in U-Boot binary that print boot-related strings
# Specifically: "Starting kernel", "Booting kernel", "cleanup_before_linux"
# Then dump them.
#
# @category ZXIC
# @runtime Jython

import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions

KEYWORDS = [
    "Starting kernel",
    "Booting kernel",
    "Booting Linux",
    "cleanup_before_linux",
    "icache_disable",
    "dcache_disable",
    "bootm_no_relocation",
]

args = getScriptArgs()
out_dir = args[0] if args else "/home/ubuntu/Projects/MYSELF/ZTE/H3600/ghidra/output_uboot"
try: os.makedirs(out_dir)
except OSError: pass
print("output -> " + out_dir)

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

# Find string addresses
mem = currentProgram.getMemory()
fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
ref_mgr = currentProgram.getReferenceManager()

def safe(s): return re.sub(r'[^a-zA-Z0-9._-]', '_', s)[:80]

found_addrs = []
data_iter = listing.getDefinedData(True)
while data_iter.hasNext():
    d = data_iter.next()
    if d.hasStringValue():
        sv = str(d.getValue())
        for kw in KEYWORDS:
            if kw in sv:
                found_addrs.append((d.getAddress(), sv[:60]))
                break

print("Strings found: %d" % len(found_addrs))
for addr, sv in found_addrs[:30]:
    print("  0x%s: %s" % (addr, sv))
    refs = ref_mgr.getReferencesTo(addr)
    funcs_to_dump = set()
    for r in refs:
        f = fm.getFunctionContaining(r.getFromAddress())
        if f:
            funcs_to_dump.add(f.getEntryPoint())
            print("    refed by func @ 0x%s (%s)" % (f.getEntryPoint(), f.getName()))
    for entry in funcs_to_dump:
        f = fm.getFunctionAt(entry)
        if not f: continue
        dr = decomp.decompileFunction(f, 60, monitor)
        if dr and dr.decompileCompleted():
            tag = safe(sv[:30])
            path = os.path.join(out_dir, "uboot_%s_%s.c" % (tag, f.getName()))
            with open(path, "w") as o:
                o.write("// uses string: %s\n" % sv)
                o.write("// function: %s @ 0x%s\n//\n" % (f.getName(), entry))
                o.write(dr.getDecompiledFunction().getC())
            print("    dumped to %s" % path)

decomp.closeProgram()
print("DONE")
