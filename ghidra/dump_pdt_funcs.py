# -*- coding: utf-8 -*-
# Dump pdt_* / zteboot_* / BootImageNum-related functions from U-Boot
# @category ZXIC
# @runtime Jython
import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions

PDT_STRINGS = [
    "pdt_getimg select = %d, serial0=0x%x, serial1=0x%x,",
    "pdt_getreal_kernelfs",
    "pdt_getimgindex",
    "zteboot_select_pdtver",
    "zteboot_select_firmware",
    "BootImageNum=0x00000001",
    "BootImageNum=%s,%ld",
    "BootImageNum",
    "Select firmware",
    "no available version!",
    "search the real offset of kernel",
    "verify_kernel readflash",
    ">>zteboot_do_settings",
    ">>s=%s, select=%d",
]
args = getScriptArgs()
out_dir = args[0] if args else "/tmp/pdt"
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
for s in PDT_STRINGS:
    for a in find_string_addrs(s):
        for r in ref_mgr.getReferencesTo(a):
            f = func_mgr.getFunctionContaining(r.getFromAddress())
            if f is not None:
                interesting.add(f.getEntryPoint())
                hits.setdefault(str(f.getName()), set()).add(s[:40])

print("Functions: %d" % len(interesting))

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
print("done")
