# Read 4 bytes at the data address and decode as ARM literal
# @category ZXIC
# @runtime Jython
import struct
args = getScriptArgs()
addr_hex = args[0] if args else "c068586c"

af = currentProgram.getAddressFactory()
mem = currentProgram.getMemory()

addr = af.getAddress(addr_hex)
print("addr: " + str(addr))
try:
    val = mem.getInt(addr) & 0xFFFFFFFF
    print("value: 0x{0:08x}".format(val))
except Exception as e:
    print("err: " + str(e))
