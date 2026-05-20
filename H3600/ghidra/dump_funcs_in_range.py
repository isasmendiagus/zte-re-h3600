# Dump all functions in address range [start, end]
# @category ZXIC
# @runtime Jython
import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions

args = getScriptArgs()
out_dir = args[0] if args else "/tmp/range"
start = args[1] if len(args) > 1 else "c0015000"
end   = args[2] if len(args) > 2 else "c0017000"
try: os.makedirs(out_dir)
except OSError: pass

af = currentProgram.getAddressFactory()
sa, ea = af.getAddress(start), af.getAddress(end)

func_mgr = currentProgram.getFunctionManager()
decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

def safe(s):
    return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:80]

dumped = 0
for f in func_mgr.getFunctions(True):
    e = f.getEntryPoint()
    if e.getOffset() < sa.getOffset() or e.getOffset() > ea.getOffset():
        continue
    name = str(f.getName())
    dr = decomp.decompileFunction(f, 60, monitor)
    if dr and dr.decompileCompleted():
        with open(os.path.join(out_dir, "{0}_{1:x}.c".format(safe(name), e.getOffset())), "w") as fp:
            fp.write("// " + name + " @ " + str(e) + "\n")
            fp.write(dr.getDecompiledFunction().getC())
        dumped += 1
        print("dumped " + name + " @ " + str(e))
decomp.closeProgram()
print("DONE " + str(dumped))
