// module: mt7915.ko
// function: Show_McastRate @ 0x27abc
// size: 284 bytes
//

undefined4 Show_McastRate(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  if ((*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) == 0) {
    uVar1 = *(uint *)(*param_1 + 0x3c) & 0xff;
    if (uVar1 < *(byte *)((int)param_1 + 0x2b7242)) {
      if (2 < DebugLevel) {
        param_1 = param_1 + uVar1 * 0x160d;
        printk("Mcast PhyMode = %d\n",*(byte *)((int)param_1 + 0x2b7d55) >> 5,param_1,0x5834,param_4
              );
        if ((2 < DebugLevel) &&
           (printk("Mcast Mcs = %d\n",*(byte *)(param_1 + 0xadf55) & 0x3f), 2 < DebugLevel)) {
          printk("Mcast BW = %d\n",((uint)*(ushort *)(param_1 + 0xadf55) << 0x17) >> 0x1e);
          return 1;
        }
      }
      return 1;
    }
    if (2 < DebugLevel) {
      printk("Invalid device interface!\n");
    }
  }
  else if (2 < DebugLevel) {
    printk("Do nothing! This device interface is NOT AP mode!\n");
  }
  return 0;
}

