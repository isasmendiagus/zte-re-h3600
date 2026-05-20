# -*- coding: utf-8 -*-
# Find all functions referencing symbols matching a pattern (e.g. uRamf040004c)
# @category ZXIC
# @runtime Jython
import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions

args = getScriptArgs()
out_dir = args[0] if args else "/tmp/by_sym"
pattern_str = args[1] if len(args) > 1 else "f04000"
try: os.makedirs(out_dir)
except OSError: pass

sym_table = currentProgram.getSymbolTable()
ref_mgr = currentProgram.getReferenceManager()
func_mgr = currentProgram.getFunctionManager()

# iterate ALL symbols, find matching
found_syms = []
it = sym_table.getAllSymbols(False)
while it.hasNext():
    s = it.next()
    name = str(s.getName())
    if pattern_str in name.lower():
        found_syms.append(s)

print("symbols matching '%s': %d" % (pattern_str, len(found_syms)))
for s in found_syms[:20]:
    print("  " + str(s.getName()) + " @ " + str(s.getAddress()))

interesting = set()
hits = {}
for s in found_syms:
    addr = s.getAddress()
    refs = ref_mgr.getReferencesTo(addr)
    for r in refs:
        f = func_mgr.getFunctionContaining(r.getFromAddress())
        if f:
            interesting.add(f.getEntryPoint())
            hits.setdefault(str(f.getName()), set()).add(str(s.getName()))

print("functions referencing them: %d" % len(interesting))

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

def safe(s): return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:80]

for entry in interesting:
    if monitor.isCancelled(): break
    f = func_mgr.getFunctionAt(entry)
    if not f: continue
    name = str(f.getName())
    dr = decomp.decompileFunction(f, 60, monitor)
    if dr and dr.decompileCompleted():
        with open(os.path.join(out_dir, "{0}_{1:x}.c".format(safe(name), entry.getOffset())), "w") as fp:
            fp.write("// " + name + " @ " + str(entry) + "\n")
            fp.write("// matched syms: " + ", ".join(sorted(hits.get(name, set()))) + "\n//\n")
            fp.write(dr.getDecompiledFunction().getC())
decomp.closeProgram()
print("done: " + str(len(interesting)))
