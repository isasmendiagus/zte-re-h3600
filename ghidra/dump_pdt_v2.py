# -*- coding: utf-8 -*-
# Force string creation at known offsets, then find xrefs.
# @category ZXIC
# @runtime Jython
import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions
from ghidra.program.model.data import StringDataType

# strings hex offsets in the raw .bin file. We need to add to image base.
STRING_OFFSETS = [
    0x51c1a,  # zteboot_select_firmware
    0x51da6,  # pdt_getreal_kernelfs
    0x51e03,  # pdt_getimgindex
    0x51e13,  # zteboot_select_pdtver
    0x5c2aa,  # pdt_getimg select = ...
    0x5c269,  # BootImageNum=0x00000001
    0x5c295,  # BootImageNum=%s,%ld
    0x5c2df,  # Select firmware
    0x5c43e,  # no available version!
    0x5c2fc,  # zteboot_do_settings
    0x5c317,  # memsize
    0x5c4c2,  # cmdline=%s
]

args = getScriptArgs()
out_dir = args[0] if args else "/tmp/pdt"
try: os.makedirs(out_dir)
except OSError: pass

mem = currentProgram.getMemory()
af = currentProgram.getAddressFactory()
listing = currentProgram.getListing()
ref_mgr = currentProgram.getReferenceManager()
func_mgr = currentProgram.getFunctionManager()

# Find image base: take first block start
blocks = mem.getBlocks()
if blocks:
    base = blocks[0].getStart().getOffset()
    print("image base = 0x%x" % base)
else:
    base = 0
    print("no blocks!")

hits_func = set()
hits_map = {}
for off in STRING_OFFSETS:
    candidate = base + off
    try:
        a = af.getAddress("%x" % candidate)
        d = listing.getDataAt(a)
        if d is None:
            try:
                listing.createData(a, StringDataType.dataType, 80)
                d = listing.getDataAt(a)
            except Exception as e2:
                print("create failed @0x%x: %s" % (candidate, e2))
                continue
        if d and d.hasStringValue():
            v = d.getDefaultValueRepresentation()
            cnt = 0
            for r in ref_mgr.getReferencesTo(a):
                cnt += 1
                f = func_mgr.getFunctionContaining(r.getFromAddress())
                if f:
                    hits_func.add(f.getEntryPoint())
                    hits_map.setdefault(str(f.getName()), []).append(v[:40])
            print("0x%x (%s): %d xrefs" % (candidate, v[:40], cnt))
        else:
            print("0x%x: no string" % candidate)
    except Exception as e:
        print("err @0x%x: %s" % (candidate, e))

print("functions: %d" % len(hits_func))

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

def safe(s): return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:80]

for entry in hits_func:
    f = func_mgr.getFunctionAt(entry)
    if not f: continue
    name = str(f.getName())
    dr = decomp.decompileFunction(f, 90, monitor)
    if dr and dr.decompileCompleted():
        with open(os.path.join(out_dir, "{0}_{1:x}.c".format(safe(name), entry.getOffset())), "w") as fp:
            fp.write("// " + name + " @ " + str(entry) + "\n")
            fp.write("// strs: " + ", ".join(hits_map.get(name, [])) + "\n//\n")
            fp.write(dr.getDecompiledFunction().getC())
decomp.closeProgram()
print("done")
