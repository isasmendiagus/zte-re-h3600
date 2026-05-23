// module: mt7915.ko
// function: set_cr4_debug @ 0xbb4b0
// size: 144 bytes
//

undefined4 set_cr4_debug(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if (-1 < DebugLevel) {
    printk(":%s: arg = %s\n","set_cr4_debug",param_2);
  }
  if (param_2 != 0) {
    uVar1 = os_str_toul(param_2,0,0x10);
    MtCmdCr4Debug(param_1,uVar1);
    return 1;
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk(":%s: Invalid parameters\n","set_cr4_debug");
  return 0;
}

