# -*- coding: utf-8 -*-
# For an ELF .ko already imported, dump every NAMED function (skip FUN_*)
# to its own .c file under <out_dir>/<binary_name>/.
# Filters by interesting prefixes if PREFIX_FILTER is non-empty.
#
# @category ZXIC
# @runtime Jython

import os
import re
from ghidra.app.decompiler import DecompInterface, DecompileOptions

# Empty = dump all named functions. Else only those starting with these.
PREFIX_FILTER = ()  # ("sw_", "mdio_", "phy_", "gephy_", "tm_", "pp_", "npp_", "idm_", "pon_", "ge_")
SKIP_PREFIXES = ("__aeabi_", "_GLOBAL_", "$d", "$t", "$a")
DECOMPILE_TIMEOUT = 60

args = getScriptArgs()
out_root = args[0] if len(args) >= 1 else "/home/ubuntu/Projects/MYSELF/ZTE/ghidra/output_ko"

# Per-program subdirectory
prog_name = currentProgram.getName()
out_dir = os.path.join(out_root, prog_name)
try: os.makedirs(out_dir)
except OSError: pass
print("output for {0} -> {1}".format(prog_name, out_dir))

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

func_mgr = currentProgram.getFunctionManager()
funcs = list(func_mgr.getFunctions(True))
print("total functions: {0}".format(len(funcs)))

named = []
for f in funcs:
    name = str(f.getName())
    if name.startswith("FUN_"): continue
    if any(name.startswith(p) for p in SKIP_PREFIXES): continue
    if PREFIX_FILTER and not any(name.startswith(p) for p in PREFIX_FILTER):
        continue
    named.append(f)
print("named (after filter): {0}".format(len(named)))

def safe(s):
    return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:100]

dumped = 0
failed = 0
for f in named:
    if monitor.isCancelled(): break
    name = str(f.getName())
    dr = decomp.decompileFunction(f, DECOMPILE_TIMEOUT, monitor)
    if dr is None or not dr.decompileCompleted():
        failed += 1
        continue
    c_code = dr.getDecompiledFunction().getC()
    fname = "{0}.c".format(safe(name))
    path = os.path.join(out_dir, fname)
    out = open(path, "w")
    out.write("// module: {0}\n".format(prog_name))
    out.write("// function: {0} @ 0x{1:x}\n".format(name, f.getEntryPoint().getOffset()))
    out.write("// size: {0} bytes\n".format(f.getBody().getNumAddresses()))
    out.write("//\n")
    out.write(c_code)
    out.close()
    dumped += 1

decomp.closeProgram()
print("DONE: {0} dumped, {1} failed".format(dumped, failed))
