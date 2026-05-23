# Find zx_map_io and dump it + the static_io_desc table it references
# @category ZXIC
# @runtime Jython
import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions

args = getScriptArgs()
out_dir = args[0] if args else "/tmp/zx_map_io"
try: os.makedirs(out_dir)
except OSError: pass

memory = currentProgram.getMemory()
listing = currentProgram.getListing()
ref_mgr = currentProgram.getReferenceManager()
func_mgr = currentProgram.getFunctionManager()

# Find any defined string ' zx_map_io ' or '======= zx_map_io ======='
target_strs = ["======= zx_map_io =======", "zx_map_io"]
for needle in target_strs:
    string_iter = listing.getDefinedData(True)
    while string_iter.hasNext():
        d = string_iter.next()
        if d.hasStringValue() and needle in d.getDefaultValueRepresentation():
            print("string '{0}' @ {1}".format(needle, d.getMinAddress()))
            refs = ref_mgr.getReferencesTo(d.getMinAddress())
            for r in refs:
                f = func_mgr.getFunctionContaining(r.getFromAddress())
                if f:
                    print("  ref from func {0} @ {1}".format(f.getName(), f.getEntryPoint()))

# Just decompile any function whose name contains "zx_map_io" or in that area
decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

def safe(s):
    return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:80]

dumped = 0
for f in func_mgr.getFunctions(True):
    name = str(f.getName())
    if "map_io" in name or "static_io" in name:
        dr = decomp.decompileFunction(f, 60, monitor)
        if dr and dr.decompileCompleted():
            with open(os.path.join(out_dir, safe(name) + ".c"), "w") as fp:
                fp.write("// " + name + " @ " + str(f.getEntryPoint()) + "\n")
                fp.write(dr.getDecompiledFunction().getC())
            dumped += 1
            print("dumped " + name)
decomp.closeProgram()
print("DONE " + str(dumped))
