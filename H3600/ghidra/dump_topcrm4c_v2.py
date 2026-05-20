# -*- coding: utf-8 -*-
# Find functions that reference the data symbol at virt 0xF040004C
# (Ghidra autonames it as DAT_f040004c or uRamf040004c).
# @category ZXIC
# @runtime Jython
import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions

args = getScriptArgs()
out_dir = args[0] if args else "/tmp/topcrm4c"
try: os.makedirs(out_dir)
except OSError: pass

af = currentProgram.getAddressFactory()
ref_mgr = currentProgram.getReferenceManager()
func_mgr = currentProgram.getFunctionManager()

target = af.getAddress("f040004c")
print("target = " + str(target))

interesting = set()
refs = ref_mgr.getReferencesTo(target)
count = 0
for r in refs:
    count += 1
    f = func_mgr.getFunctionContaining(r.getFromAddress())
    if f:
        interesting.add(f.getEntryPoint())
print("refs to target: %d, unique funcs: %d" % (count, len(interesting)))

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

def safe(s): return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:80]

for entry in interesting:
    f = func_mgr.getFunctionAt(entry)
    if not f: continue
    name = str(f.getName())
    dr = decomp.decompileFunction(f, 60, monitor)
    if dr and dr.decompileCompleted():
        with open(os.path.join(out_dir, "{0}_{1:x}.c".format(safe(name), entry.getOffset())), "w") as fp:
            fp.write("// " + name + " @ " + str(entry) + "\n")
            fp.write(dr.getDecompiledFunction().getC())
decomp.closeProgram()
print("done: " + str(len(interesting)))
