// module: mt7915.ko
// function: MlmeRadioOff @ 0x12c9e4
// size: 104 bytes
//

void MlmeRadioOff(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  undefined4 uVar1;
  undefined4 extraout_r2_00;
  
  if (param_2 == (int *)0x0) {
    return;
  }
  if (*(int *)(*param_2 + 0x240) == 0) {
    warn_slowpath_null("include/linux/netdevice.h",0xa06);
    printk(&_LC46);
    uVar1 = extraout_r2_00;
  }
  else {
    _set_bit(0,*(int *)(*param_2 + 0x240) + 0x50);
    uVar1 = extraout_r2;
  }
  *(undefined1 *)(param_2 + 0x2b0) = 0;
  MTRadioOff(param_1,param_2,uVar1,param_4);
  return;
}

