// module: mt7915.ko
// function: set_cr4_query @ 0xbb238
// size: 156 bytes
//

undefined4 set_cr4_query(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if (DebugLevel < 1) {
    if (param_2 == 0) {
      return 0;
    }
  }
  else {
    printk(":%s: arg = %s\n","set_cr4_query",param_2);
    if (param_2 == 0) {
      if (DebugLevel < 1) {
        return 0;
      }
      printk(":%s: Invalid parameters\n","set_cr4_query");
      return 0;
    }
  }
  uVar1 = os_str_toul(param_2,0,0x10);
  MtCmdCr4Query(param_1,uVar1,0,0);
  return 1;
}

