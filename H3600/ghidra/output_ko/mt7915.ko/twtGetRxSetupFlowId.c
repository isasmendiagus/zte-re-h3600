// module: mt7915.ko
// function: twtGetRxSetupFlowId @ 0x168ae0
// size: 48 bytes
//

uint twtGetRxSetupFlowId(int param_1)

{
  if (param_1 == 0) {
    printk(&_LC24,0x61b);
    dump_stack();
  }
  return ((uint)*(ushort *)(param_1 + 3) << 0x16) >> 0x1d;
}

