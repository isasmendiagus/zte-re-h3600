# -*- coding: utf-8 -*-
# Force-create a function at given address and decompile it
# @category ZXIC
# @runtime Jython
import os
from ghidra.app.decompiler import DecompInterface, DecompileOptions
from ghidra.program.model.symbol import SourceType
from ghidra.app.cmd.function import CreateFunctionCmd

args = getScriptArgs()
out_dir = args[0] if args else "/tmp/forced"
addr_hex = args[1] if len(args) > 1 else "c0015a74"
try: os.makedirs(out_dir)
except OSError: pass

af = currentProgram.getAddressFactory()
addr = af.getAddress(addr_hex)
print("target: " + str(addr))

func_mgr = currentProgram.getFunctionManager()
f = func_mgr.getFunctionAt(addr)
if f is None:
    print("not a function - creating one")
    cmd = CreateFunctionCmd(addr)
    if not cmd.applyTo(currentProgram, monitor):
        print("failed to create function")
    f = func_mgr.getFunctionAt(addr)

if f is None:
    print("still no function - give up")
else:
    decomp = DecompInterface()
    decomp.setOptions(DecompileOptions())
    decomp.openProgram(currentProgram)
    dr = decomp.decompileFunction(f, 90, monitor)
    if dr and dr.decompileCompleted():
        with open(os.path.join(out_dir, "FUN_" + addr_hex + ".c"), "w") as fp:
            fp.write("// " + str(f.getName()) + " @ " + str(f.getEntryPoint()) + "\n")
            fp.write(dr.getDecompiledFunction().getC())
        print("dumped")
    else:
        print("FAILED")
    decomp.closeProgram()
