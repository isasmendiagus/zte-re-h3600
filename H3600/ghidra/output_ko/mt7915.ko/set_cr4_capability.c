// module: mt7915.ko
// function: set_cr4_capability @ 0xbb418
// size: 148 bytes
//

undefined4 set_cr4_capability(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if (DebugLevel < 1) {
    if (param_2 == 0) {
      return 0;
    }
  }
  else {
    printk(":%s: arg = %s\n","set_cr4_capability",param_2);
    if (param_2 == 0) {
      if (DebugLevel < 1) {
        return 0;
      }
      printk(":%s: Invalid parameters\n","set_cr4_capability");
      return 0;
    }
  }
  uVar1 = os_str_toul(param_2,0,0x10);
  MtCmdCr4Capability(param_1,uVar1);
  return 1;
}

