# Dump the iotable_init table at DAT_c065e6b0 (19 entries of struct map_desc)
# struct map_desc { unsigned long virtual; unsigned long pfn; unsigned long length; unsigned int type; }
# = 16 bytes on ARM 32-bit
# @category ZXIC
# @runtime Jython
import os

args = getScriptArgs()
out_path = args[0] if args else "/tmp/static_io_table.txt"

af = currentProgram.getAddressFactory()
mem = currentProgram.getMemory()

base = af.getAddress("c065e6b0")
n_entries = 19
ENTRY_SIZE = 16

def readu32(a):
    return mem.getInt(a) & 0xFFFFFFFF

with open(out_path, "w") as fp:
    fp.write("static_io_desc[] @ " + str(base) + "\n")
    fp.write("idx   virtual    phys (pfn<<12)   length     type\n")
    for i in range(n_entries):
        a = base.add(i * ENTRY_SIZE)
        v = readu32(a)
        p = readu32(a.add(4))
        l = readu32(a.add(8))
        t = readu32(a.add(12))
        line = "{0:3d}: 0x{1:08x}  0x{2:08x}  0x{3:08x}  {4}\n".format(
            i, v, p << 12, l, t)
        fp.write(line)
        print(line.rstrip())

print("DONE -> " + out_path)
