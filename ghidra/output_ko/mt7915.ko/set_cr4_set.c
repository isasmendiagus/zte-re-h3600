// module: mt7915.ko
// function: set_cr4_set @ 0xbb2d8
// size: 316 bytes
//

undefined4 set_cr4_set(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char *local_24 [2];
  
  local_24[0] = param_2;
  if (0 < DebugLevel) {
    printk(":%s: arg = %s\n","set_cr4_set",param_2);
  }
  pcVar1 = strsep(local_24,":");
  pcVar2 = strsep(local_24,":");
  if ((pcVar2 != (char *)0x0 && pcVar1 != (char *)0x0) && (local_24[0] != (char *)0x0)) {
    uVar3 = os_str_toul(pcVar1,0,0x10);
    uVar4 = os_str_toul(pcVar2,0,0x10);
    uVar5 = os_str_toul(local_24[0],0,0x10);
    if (0 < DebugLevel) {
      printk("%s: arg0 = 0x%x, arg1 = 0x%x, arg2 = 0x%x\n","set_cr4_set",uVar3,uVar4,uVar5);
    }
    MtCmdCr4Set(param_1,uVar3,uVar4,uVar5);
    return 1;
  }
  if (0 < DebugLevel) {
    printk(":%s: Invalid parameters\n","set_cr4_set");
  }
  return 0;
}

