# -*- coding: utf-8 -*-
# @category ZXIC
# @runtime Jython

func_mgr = currentProgram.getFunctionManager()
funcs = list(func_mgr.getFunctions(True))
print("TOTAL FUNCTIONS: {0}".format(len(funcs)))

named = [f for f in funcs if not f.getName().startswith("FUN_")]
print("NAMED FUNCTIONS: {0}".format(len(named)))
for f in named[:20]:
    print("  {0}  @ {1}".format(f.getName(), f.getEntryPoint()))

# Check function before some peripheral literal addresses
test_addrs = [0xc04b9000, 0xc0660000, 0xc05b7000]
addr_factory = currentProgram.getAddressFactory()
addr_space = addr_factory.getDefaultAddressSpace()
for a in test_addrs:
    aobj = addr_space.getAddress(a)
    f = func_mgr.getFunctionBefore(aobj)
    print("getFunctionBefore(0x{0:x}) = {1}".format(
        a, f.getName() + " @ " + str(f.getEntryPoint()) if f else "None"))

# Memory blocks
mem = currentProgram.getMemory()
for b in mem.getBlocks():
    print("BLOCK: {0} 0x{1:x}-0x{2:x} init={3} loaded={4}".format(
        b.getName(),
        b.getStart().getOffset(),
        b.getEnd().getOffset(),
        b.isInitialized(), b.isLoaded()))
