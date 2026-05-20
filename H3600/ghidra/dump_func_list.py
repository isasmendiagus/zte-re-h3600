# Dump multiple functions by entry address (comma-separated list of hex addrs)
# @category ZXIC
# @runtime Jython
import os
from ghidra.app.decompiler import DecompInterface, DecompileOptions

args = getScriptArgs()
out_dir = args[0] if args else "/tmp/dump"
addr_list = args[1].split(",") if len(args) > 1 else []
try: os.makedirs(out_dir)
except OSError: pass

af = currentProgram.getAddressFactory()
fm = currentProgram.getFunctionManager()
decomp = DecompInterface(); decomp.setOptions(DecompileOptions()); decomp.openProgram(currentProgram)

for ah in addr_list:
    addr = af.getAddress(ah)
    f = fm.getFunctionAt(addr) or fm.getFunctionContaining(addr)
    if f is None:
        print("no func at " + ah); continue
    dr = decomp.decompileFunction(f, 90, monitor)
    if dr and dr.decompileCompleted():
        path = os.path.join(out_dir, "FUN_" + ah + ".c")
        with open(path, "w") as fp:
            fp.write("// " + f.getName() + " @ " + str(f.getEntryPoint()) + " size=" + str(f.getBody().getNumAddresses()) + "\n")
            fp.write(dr.getDecompiledFunction().getC())
        print("dumped " + ah + " -> " + path)
    else:
        print("FAILED " + ah)
decomp.closeProgram()
