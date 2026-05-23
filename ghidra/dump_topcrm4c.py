# -*- coding: utf-8 -*-
# Find functions that touch TOPCRM offset 0x4C (virt 0xF040004C)
# Specifically looking for USB-related clock enable bits.
# @category ZXIC
# @runtime Jython
import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions

args = getScriptArgs()
out_dir = args[0] if args else "/tmp/topcrm4c"
try: os.makedirs(out_dir)
except OSError: pass

# Find any reference / use of address 0xF040004C
af = currentProgram.getAddressFactory()
ref_mgr = currentProgram.getReferenceManager()
func_mgr = currentProgram.getFunctionManager()
listing = currentProgram.getListing()

# Heuristic: search for the constant 0xf040004c in code
# We look at all defined data and functions for uses of that address
target = 0xf040004c

interesting = set()
for f in func_mgr.getFunctions(True):
    if monitor.isCancelled(): break
    body = f.getBody()
    addr = body.getMinAddress()
    if addr is None: continue
    end = body.getMaxAddress()
    cur = addr
    while cur is not None and cur.getOffset() <= end.getOffset():
        try:
            instr = listing.getInstructionAt(cur)
            if instr is not None:
                ops = instr.getOpObjects(0)
                for o in ops:
                    s = str(o)
                    if "0xf040004c" in s.lower() or "0xf040004" in s.lower():
                        interesting.add(f.getEntryPoint())
                        break
                if f.getEntryPoint() in interesting: break
                ops = instr.getOpObjects(1)
                for o in ops:
                    s = str(o)
                    if "0xf040004c" in s.lower():
                        interesting.add(f.getEntryPoint())
                        break
                if f.getEntryPoint() in interesting: break
        except: pass
        nxt = cur.next()
        if nxt is None: break
        cur = nxt

print("found %d functions touching virt 0xF040004C area" % len(interesting))

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

def safe(s): return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:80]

for entry in interesting:
    f = func_mgr.getFunctionAt(entry)
    name = str(f.getName())
    dr = decomp.decompileFunction(f, 60, monitor)
    if dr and dr.decompileCompleted():
        with open(os.path.join(out_dir, "{0}_{1:x}.c".format(safe(name), entry.getOffset())), "w") as fp:
            fp.write("// " + name + " @ " + str(entry) + "\n")
            fp.write(dr.getDecompiledFunction().getC())
decomp.closeProgram()
print("done")
