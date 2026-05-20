// module: mt7915.ko
// function: Set_EntryLifeCheck_Proc @ 0x34084
// size: 136 bytes
//

undefined4
Set_EntryLifeCheck_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  if (uVar1 < 0x10000) {
    *(uint *)(&DAT_0036b910 + param_1) = uVar1;
  }
  else {
    if (DebugLevel < 3) {
      return 1;
    }
    printk("LifeCheckCnt must in range of 0 to 65535\n");
  }
  if (2 < DebugLevel) {
    printk("EntryLifeCheck Cnt = %ld.\n",*(undefined4 *)(&DAT_0036b910 + param_1));
  }
  return 1;
}

