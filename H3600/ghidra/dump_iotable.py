# Dump iotable_init array (struct map_desc) at given address
# @category ZXIC
# @runtime Jython
import os, sys
args = getScriptArgs()
addr_hex = args[0] if args else "c065e6b0"
n = int(args[1]) if len(args) > 1 else 19

af = currentProgram.getAddressFactory()
mem = currentProgram.getMemory()
addr = af.getAddress(addr_hex)
print("table @ " + str(addr) + " entries=" + str(n))
print("idx  virtual    pfn(phys)   length     type")
for i in range(n):
    base = addr.add(i * 16)
    try:
        v = mem.getInt(base) & 0xFFFFFFFF
        pfn = mem.getInt(base.add(4)) & 0xFFFFFFFF
        length = mem.getInt(base.add(8)) & 0xFFFFFFFF
        t = mem.getInt(base.add(12)) & 0xFFFFFFFF
        phys = (pfn << 12) & 0xFFFFFFFF
        print("{0:2d}   0x{1:08x} 0x{2:08x}  0x{3:08x} {4}  (phys 0x{5:08x})".format(
            i, v, pfn, length, t, phys))
    except Exception as e:
        print("{0:2d}   ERR: {1}".format(i, e))
