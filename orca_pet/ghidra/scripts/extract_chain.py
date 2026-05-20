# -*- coding: utf-8 -*-
# Drive extraction by following the OF_DECLARE chain:
#   compat string in .rodata
#     <- LE32 ptr inside an of_device_id-like struct in .rodata
#         struct contains: compat_ptr [+ name/type filler] [+ data/init_func ptr]
#   pull each plausible function pointer found in the struct, decompile it.
#
# Also handle of_device_id arrays where compatible[128] is INLINED (so no
# explicit ptr — follow the array address backwards).
#
# @category ZXIC
# @runtime Jython

import os
import re
import struct
import bisect
from jarray import zeros
from ghidra.app.decompiler import DecompInterface, DecompileOptions

PREFIXES = ("zte,", "snps,", "denali,", "zxic,", "arm,zx", "rohm,")
DECOMPILE_TIMEOUT = 90

# Kernel virtual range — derived from extracted DTS / load addr 0x40008000
# mapped to virt 0xC0008000 (PAGE_OFFSET = 0xC0000000).
KMIN = 0xC0008000
KMAX = 0xC0700000  # generous upper bound

args = getScriptArgs()
out_dir = args[0] if len(args) >= 1 else "/home/ubuntu/Projects/MYSELF/ZTE/ghidra/output_chain"
try: os.makedirs(out_dir)
except OSError: pass
print("output -> " + out_dir)

decomp = DecompInterface()
decomp.setOptions(DecompileOptions())
decomp.openProgram(currentProgram)

mem = currentProgram.getMemory()
func_mgr = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
addr_factory = currentProgram.getAddressFactory()
addr_space = addr_factory.getDefaultAddressSpace()

# Read all memory blocks
mem_dump = []
for b in mem.getBlocks():
    if not b.isInitialized() or not b.isLoaded(): continue
    sz = int(b.getSize())
    if sz > 64*1024*1024: continue
    jbarr = zeros(sz, 'b')
    try: mem.getBytes(b.getStart(), jbarr)
    except: continue
    data_str = "".join(chr(x & 0xff) for x in jbarr)
    mem_dump.append((b.getStart().getOffset(), data_str))
print("loaded {0} memory blocks".format(len(mem_dump)))

def read_str(off, maxlen=200):
    for base, data in mem_dump:
        if base <= off < base + len(data):
            local = off - base
            end = data.find("\x00", local, local + maxlen)
            if end < 0: return None
            return data[local:end]
    return None

def read_le32(off):
    for base, data in mem_dump:
        if base <= off < base + len(data) - 3:
            local = off - base
            return struct.unpack("<I", data[local:local+4])[0]
    return None

def find_le32_refs(target_addr):
    needle = struct.pack("<I", target_addr & 0xffffffff)
    out = []
    for base, data in mem_dump:
        i = 0
        while True:
            j = data.find(needle, i)
            if j < 0: break
            if j % 4 == 0: out.append(base + j)
            i = j + 1
    return out

def find_string_occurrences(s):
    nb = s + "\x00"
    out = []
    for base, data in mem_dump:
        i = 0
        while True:
            j = data.find(nb, i)
            if j < 0: break
            # boundary check: prev byte should be NUL or non-ASCII
            ok = True
            if j > 0 and 0x20 <= ord(data[j-1]) <= 0x7e:
                ok = False
            if ok: out.append(base + j)
            i = j + 1
    return out

# Build sorted func list for nearest-before
all_funcs = sorted(func_mgr.getFunctions(True), key=lambda f: f.getEntryPoint().getOffset())
all_func_offsets = [f.getEntryPoint().getOffset() for f in all_funcs]
print("functions indexed: {0}".format(len(all_funcs)))

def is_likely_function(addr):
    if not (KMIN <= addr < KMAX): return None
    aobj = addr_space.getAddress(addr & 0xfffffffe)  # mask thumb bit
    f = func_mgr.getFunctionAt(aobj)
    if f is not None: return f
    # try +- some offsets (function may have been mis-detected)
    return None

# 1) Find all compat strings in memory
compat_strings = {}
for base, data in mem_dump:
    for prefix in PREFIXES:
        i = 0
        while True:
            j = data.find(prefix, i)
            if j < 0: break
            # NUL/non-printable boundary check
            if j > 0 and 0x20 <= ord(data[j-1]) <= 0x7e:
                i = j + 1; continue
            s = read_str(base + j)
            if s and 5 < len(s) < 128 and all(0x20 <= ord(c) <= 0x7e for c in s):
                compat_strings.setdefault(s, []).append(base + j)
            i = j + 1
print("compat strings found: {0}".format(len(compat_strings)))

dumped_funcs = set()
index_lines = [
    "# OF_DECLARE chain extraction",
    "",
    "For each compatible string, follow LE32 refs into struct, dump function ptrs.",
    "",
    "| Compatible | str addr | refs to str | func ptrs found | decompiled |",
    "|---|---|---|---|---|",
]

def safe(s):
    return re.sub(r"[^a-zA-Z0-9._-]", "_", s)[:80]

for compat in sorted(compat_strings.keys()):
    if monitor.isCancelled(): break
    occurrences = compat_strings[compat]
    candidate_funcs = set()

    # 1) For each compat string occurrence S, the of_device_id struct in Linux 4.x
    # has compat[128] at offset +64. So struct starts at S-64. Try multiple
    # struct layouts: compat at offsets {0, 32, 64, 96, 128} relative to struct.
    struct_starts = set()
    for occ in occurrences:
        for compat_off in (0, 32, 64, 96, 128):
            ss = occ - compat_off
            if ss < KMIN: continue
            struct_starts.add((ss, compat_off))

    # 2) For each potential struct start, find LE32 refs to it.
    str_refs_total = 0
    all_struct_refs = []  # collect for pass 3
    for (ss, compat_off) in struct_starts:
        refs = find_le32_refs(ss)
        if not refs:
            continue
        str_refs_total += len(refs)
        for ref in refs:
            all_struct_refs.append((ref, compat_off))
            # 2a) Function containing the ref → driver code that uses the table
            ref_obj = addr_space.getAddress(ref)
            f = func_mgr.getFunctionContaining(ref_obj)
            if f is None:
                idx = bisect.bisect_right(all_func_offsets, ref) - 1
                if 0 <= idx < len(all_funcs):
                    cand = all_funcs[idx]
                    if ref - cand.getBody().getMaxAddress().getOffset() < 4096:
                        f = cand
            if f is not None:
                candidate_funcs.add((f.getEntryPoint().getOffset(),
                                    str(f.getName()), 0))

        # 2b) Read the data/init_fn field of the struct (CLK_OF_DECLARE pattern)
        for data_off in (compat_off + 128, compat_off + 132,
                         compat_off + 4, 4, 8):
            v = read_le32(ss + data_off)
            if v is None: continue
            if not (KMIN <= v < KMAX): continue
            f = is_likely_function(v)
            if f is not None:
                candidate_funcs.add((f.getEntryPoint().getOffset(),
                                    str(f.getName()), v))

    # 3) platform_driver pattern. The ref R to the of_device_id array sits
    # inside a `struct device_driver` which is wrapped in `struct platform_driver`.
    # In Linux 4.1, platform_driver layout (32-bit ARM):
    #   probe(0), remove(4), shutdown(8), suspend(12), resume(16),
    #   driver{...} starting at +20:
    #     name(0), bus(4), owner(8), mod_name(12), suppress_bind_attrs(16,bool+pad),
    #     probe_type(20), of_match_table(24)
    # So of_match_table is at platform_driver offset 20+24 = 44.
    # The platform_driver.probe is at offset 0. So the probe pointer
    # is at (R - 44).
    #
    # But there are simpler structs (clk_init_data, irq_chip, etc.) that
    # may use the of_device_id array directly. Be defensive: scan
    # negative offsets -64..-4 looking for code pointers.
    for (R, compat_off) in all_struct_refs:
        for neg in range(4, 80, 4):
            v = read_le32(R - neg)
            if v is None: continue
            if not (KMIN <= v < KMAX): continue
            f = is_likely_function(v)
            if f is not None:
                candidate_funcs.add((f.getEntryPoint().getOffset(),
                                    str(f.getName()), v))
        # Also positive offsets (in case ref is at start of struct)
        for pos in range(4, 64, 4):
            v = read_le32(R + pos)
            if v is None: continue
            if not (KMIN <= v < KMAX): continue
            f = is_likely_function(v)
            if f is not None:
                candidate_funcs.add((f.getEntryPoint().getOffset(),
                                    str(f.getName()), v))

    all_str_refs_count = str_refs_total

    extracted_names = []
    for entry, name, src_ptr in candidate_funcs:
        if entry in dumped_funcs:
            extracted_names.append("{0}__dup".format(name))
            continue
        dumped_funcs.add(entry)
        f = func_mgr.getFunctionAt(addr_space.getAddress(entry))
        if f is None: continue
        dr = decomp.decompileFunction(f, DECOMPILE_TIMEOUT, monitor)
        if dr is None or not dr.decompileCompleted():
            extracted_names.append("{0}__decompfail".format(name))
            continue
        c_code = dr.getDecompiledFunction().getC()
        fname = "{0}__{1}.c".format(safe(compat), safe(name))
        path = os.path.join(out_dir, fname)
        out = open(path, "w")
        out.write("// compatible: {0}\n".format(compat))
        out.write("// function: {0} @ 0x{1:x}\n".format(name, entry))
        if src_ptr:
            out.write("// found via struct field ptr -> 0x{0:x}\n".format(src_ptr))
        else:
            out.write("// found via xref to compat string\n")
        out.write("// total struct-refs for compat: {0}\n".format(all_str_refs_count))
        out.write("//\n")
        out.write(c_code)
        out.close()
        extracted_names.append(name)

    line = "| `{0}` | 0x{1:x} | {2} | {3} | {4} |".format(
        compat, occurrences[0], all_str_refs_count,
        len(candidate_funcs),
        ", ".join(extracted_names) if extracted_names else "(none)")
    index_lines.append(line)

f = open(os.path.join(out_dir, "INDEX.md"), "w")
f.write("\n".join(index_lines))
f.write("\n")
f.close()

decomp.closeProgram()
print("DONE: {0} compat strings, {1} unique driver funcs decompiled".format(
    len(compat_strings), len(dumped_funcs)))
