# Dump one function by entry address
# @category ZXIC
# @runtime Jython
import os
from ghidra.app.decompiler import DecompInterface, DecompileOptions
from ghidra.program.model.address import AddressFactory

args = getScriptArgs()
out_dir = args[0] if args else "/tmp/one"
addr_hex = args[1] if len(args) > 1 else "c0639098"
try: os.makedirs(out_dir)
except OSError: pass

af = currentProgram.getAddressFactory()
addr = af.getAddress(addr_hex)
print("target addr: " + str(addr))

func_mgr = currentProgram.getFunctionManager()
f = func_mgr.getFunctionAt(addr)
if f is None:
    f = func_mgr.getFunctionContaining(addr)
print("function: " + str(f))

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)
dr = decomp.decompileFunction(f, 90, monitor)
if dr and dr.decompileCompleted():
    fp = open(os.path.join(out_dir, "FUN_" + addr_hex + ".c"), "w")
    fp.write("// " + f.getName() + " @ " + str(f.getEntryPoint()) + "\n")
    fp.write(dr.getDecompiledFunction().getC())
    fp.close()
    print("dumped")
else:
    print("FAILED")
decomp.closeProgram()
