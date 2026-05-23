# -*- coding: utf-8 -*-
# Dump function FUN_c000e9c4 (registration helper) and find what calls setup_port
# @category ZXIC
# @runtime Jython
import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions

args = getScriptArgs()
out_dir = args[0] if args else "/tmp/pcie_more"
try: os.makedirs(out_dir)
except OSError: pass

af = currentProgram.getAddressFactory()
func_mgr = currentProgram.getFunctionManager()
ref_mgr = currentProgram.getReferenceManager()
listing = currentProgram.getListing()

# Functions of interest
TARGETS = ["c000e9c4", "c001605c", "c00168a4", "c0015e04", "c00169c8"]
# Find functions that REFERENCE FUN_c001605c (synopsys_pcie_setup)
setup_addr = af.getAddress("c001605c")
refs_to_setup = list(ref_mgr.getReferencesTo(setup_addr))
print("refs to FUN_c001605c (setup_port): " + str(len(refs_to_setup)))
callers = set()
for r in refs_to_setup:
    f = func_mgr.getFunctionContaining(r.getFromAddress())
    if f:
        callers.add(f.getEntryPoint().getOffset())
        print("  caller: 0x" + format(f.getEntryPoint().getOffset(), "x"))

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

def dump(addr_hex):
    a = af.getAddress(addr_hex)
    f = func_mgr.getFunctionAt(a)
    if not f:
        f = func_mgr.getFunctionContaining(a)
    if not f:
        print("no function at " + addr_hex)
        return
    name = str(f.getName())
    dr = decomp.decompileFunction(f, 90, monitor)
    if dr and dr.decompileCompleted():
        path = os.path.join(out_dir, "{0}_{1:x}.c".format(re.sub(r"[^a-zA-Z0-9]", "_", name), f.getEntryPoint().getOffset()))
        with open(path, "w") as fp:
            fp.write("// " + name + " @ " + str(f.getEntryPoint()) + "\n")
            fp.write(dr.getDecompiledFunction().getC())
        print("dumped " + path)

# Dump targets
for t in TARGETS:
    dump(t)
# Dump callers of setup_port
for c in callers:
    dump("%x" % c)

decomp.closeProgram()
print("done")
