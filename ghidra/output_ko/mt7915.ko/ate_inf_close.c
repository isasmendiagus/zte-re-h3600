// module: mt7915.ko
// function: ate_inf_close @ 0x27f970
// size: 76 bytes
//

undefined4 ate_inf_close(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r2;
  
  if (*(int *)(param_1 + 8) != 0) {
    iVar1 = wifi_sys_close();
    if (iVar1 == 1) {
      return 1;
    }
    if (2 < DebugLevel) {
      printk("%s() close fail!!!\n","ate_inf_close",extraout_r2,DebugLevel,param_4);
    }
  }
  return 0;
}

