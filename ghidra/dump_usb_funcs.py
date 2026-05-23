# -*- coding: utf-8 -*-
# Find functions referencing USB/DWC2/DWC3 strings and decompile them
# @category ZXIC
# @runtime Jython
import os, re
from ghidra.app.decompiler import DecompInterface, DecompileOptions

USB_STRINGS = [
    "zx279121-dwc3",
    "zte,zx279128-dwc3",
    "zte,zx279127-dwc2",
    "couldn't allocate dwc3 device",
    "couldn't add resources to dwc3 device",
    "failed to register dwc3 device",
    "failed to alloc mem dwc3 core",
    "failed to create dwc3 core",
    "usb_bus_clk",
    "usb_ref_clk0",
    "usb_ref_clk1",
]
args = getScriptArgs()
out_dir = args[0] if args else "/tmp/usb_funcs"
try: os.makedirs(out_dir)
except OSError: pass

memory = currentProgram.getMemory()
listing = currentProgram.getListing()
ref_mgr = currentProgram.getReferenceManager()
func_mgr = currentProgram.getFunctionManager()

def find_string_addrs(needle):
    addrs = []
    string_iter = listing.getDefinedData(True)
    while string_iter.hasNext():
        d = string_iter.next()
        if d.hasStringValue() and needle in d.getDefaultValueRepresentation():
            addrs.append(d.getMinAddress())
    return addrs

interesting = set()
hits = {}
for s in USB_STRINGS:
    addrs = find_string_addrs(s)
    if not addrs:
        print("[!] not found: " + s)
        continue
    for a in addrs:
        for r in ref_mgr.getReferencesTo(a):
            f = func_mgr.getFunctionContaining(r.getFromAddress())
            if f is not None:
                interesting.add(f.getEntryPoint())
                hits.setdefault(str(f.getName()), set()).add(s)
        print("[+] '{0}' -> defined".format(s[:40]))

print("\n=== Functions found: %d ===" % len(interesting))

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

def safe(s): return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:80]

dumped = 0
for entry in interesting:
    if monitor.isCancelled(): break
    f = func_mgr.getFunctionAt(entry)
    if not f: continue
    name = str(f.getName())
    dr = decomp.decompileFunction(f, 90, monitor)
    if dr and dr.decompileCompleted():
        with open(os.path.join(out_dir, "{0}_{1:x}.c".format(safe(name), entry.getOffset())), "w") as fp:
            fp.write("// " + name + " @ " + str(entry) + "\n")
            fp.write("// matched: " + ", ".join(sorted(hits.get(name, set()))) + "\n//\n")
            fp.write(dr.getDecompiledFunction().getC())
        dumped += 1
decomp.closeProgram()
print("DONE: %d dumped" % dumped)
