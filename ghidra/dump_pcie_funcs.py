# -*- coding: utf-8 -*-
# Find functions that reference PCIe-related strings in vmlinux.bin
# and decompile them.
#
# @category ZXIC
# @runtime Jython

import os
import re
from ghidra.app.decompiler import DecompInterface, DecompileOptions
from ghidra.program.model.symbol import RefType

PCIE_STRINGS = [
    "synopsys pcie probe enter!!!!!!",
    "pcie reg base %x",
    "synopsys pcie%d controller setting",
    "synopsys pcie%d controller waitting L0 state",
    "pcie%d link up,gen%d,cnt %d!",
    "pcie%d vendor id is 0x%0x",
    "pcie%d device id is 0x%0x",
    "request pcie irq failed",
    "pcie0 mem space",
    "pcie1 mem space",
    "pcie0 reg",
    "pcie1 reg",
    "pcie0 irq is %d",
    "pcie1 irq is %d",
    "zte,zx279127-pcie",
    "zte,ZX279127-pcie",
    "Request PCIe Memory resource failed",
    "not find pcie port:%d",
    "synopsys pcie port%d controller debug print",
    "error! no such port",
]

DECOMPILE_TIMEOUT = 90

args = getScriptArgs()
out_dir = args[0] if len(args) >= 1 else "/tmp/pcie_funcs"
try: os.makedirs(out_dir)
except OSError: pass
print("output -> " + out_dir)

memory = currentProgram.getMemory()
listing = currentProgram.getListing()
ref_mgr = currentProgram.getReferenceManager()
func_mgr = currentProgram.getFunctionManager()

def find_string_addrs(needle):
    """Find every address that contains the byte sequence of `needle`."""
    addrs = []
    needle_bytes = bytearray(needle, "ascii") + b"\x00"
    blocks = memory.getBlocks()
    for blk in blocks:
        if not blk.isInitialized(): continue
        if blk.getName() in ("ram", "RAM"): pass
        # Use Ghidra search
    # Simpler: walk listing for defined strings
    string_iter = listing.getDefinedData(True)
    while string_iter.hasNext():
        d = string_iter.next()
        if d.hasStringValue():
            v = d.getDefaultValueRepresentation()
            # strip surrounding quotes that Ghidra adds
            if needle in v:
                addrs.append(d.getMinAddress())
    return addrs

interesting_funcs = set()
hits = {}

for s in PCIE_STRINGS:
    addrs = find_string_addrs(s)
    if not addrs:
        print("[!] not found: " + s)
        continue
    for a in addrs:
        refs = ref_mgr.getReferencesTo(a)
        for r in refs:
            from_addr = r.getFromAddress()
            f = func_mgr.getFunctionContaining(from_addr)
            if f is not None:
                interesting_funcs.add(f.getEntryPoint())
                hits.setdefault(str(f.getName()), []).append(s)
        print("[+] '{0}' -> {1} refs".format(s[:40], len(list(refs)) if refs else 0))

print("\n=== Functions found ===")
for n, ss in hits.items():
    print("  {0}: {1}".format(n, len(ss)))

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

def safe(s):
    return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:100]

dumped = 0
for entry in interesting_funcs:
    if monitor.isCancelled(): break
    f = func_mgr.getFunctionAt(entry)
    if f is None: continue
    name = str(f.getName())
    dr = decomp.decompileFunction(f, DECOMPILE_TIMEOUT, monitor)
    if dr is None or not dr.decompileCompleted():
        print("[!] failed: " + name)
        continue
    c_code = dr.getDecompiledFunction().getC()
    fname = "{0}_{1:x}.c".format(safe(name), entry.getOffset())
    path = os.path.join(out_dir, fname)
    out = open(path, "w")
    out.write("// vmlinux.bin: " + name + " @ 0x{0:x}\n".format(entry.getOffset()))
    out.write("// matched strings: " + ", ".join(hits.get(name, [])) + "\n//\n")
    out.write(c_code)
    out.close()
    dumped += 1

decomp.closeProgram()
print("DONE: {0} dumped to {1}".format(dumped, out_dir))
