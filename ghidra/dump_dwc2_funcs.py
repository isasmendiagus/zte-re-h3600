# -*- coding: utf-8 -*-
# @category ZXIC
# @runtime Jython
import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions

DWC2_STRINGS = [
    "snps,dwc2",
    "dwc2_hcd_init",
    "dwc2_core_init",
    "FS PHY selected at HS!",
    "Hardware does not support descriptor DMA mode",
    "couldn't allocate dwc2 device",
    "couldn't add resources to dwc2 device",
]
args = getScriptArgs()
out_dir = args[0] if args else "/tmp/dwc2"
try: os.makedirs(out_dir)
except OSError: pass

memory = currentProgram.getMemory()
listing = currentProgram.getListing()
ref_mgr = currentProgram.getReferenceManager()
func_mgr = currentProgram.getFunctionManager()

def find_string_addrs(needle):
    addrs = []
    string_iter = listing.getDefinedData(True)
    while string_iter.hasNext():
        d = string_iter.next()
        if d.hasStringValue() and needle in d.getDefaultValueRepresentation():
            addrs.append(d.getMinAddress())
    return addrs

interesting = set()
hits = {}
for s in DWC2_STRINGS:
    for a in find_string_addrs(s):
        for r in ref_mgr.getReferencesTo(a):
            f = func_mgr.getFunctionContaining(r.getFromAddress())
            if f is not None:
                interesting.add(f.getEntryPoint())
                hits.setdefault(str(f.getName()), set()).add(s)

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

def safe(s): return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:80]

for entry in interesting:
    if monitor.isCancelled(): break
    f = func_mgr.getFunctionAt(entry)
    if not f: continue
    name = str(f.getName())
    dr = decomp.decompileFunction(f, 90, monitor)
    if dr and dr.decompileCompleted():
        with open(os.path.join(out_dir, "{0}_{1:x}.c".format(safe(name), entry.getOffset())), "w") as fp:
            fp.write("// " + name + " @ " + str(entry) + "\n")
            fp.write("// matched: " + ", ".join(sorted(hits.get(name, set()))) + "\n//\n")
            fp.write(dr.getDecompiledFunction().getC())
decomp.closeProgram()
print("DONE: " + str(len(interesting)) + " functions")
