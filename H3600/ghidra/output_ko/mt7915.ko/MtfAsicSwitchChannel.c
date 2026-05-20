// module: mt7915.ko
// function: MtfAsicSwitchChannel @ 0x195318
// size: 136 bytes
//

void MtfAsicSwitchChannel
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x54) == (code *)0x0) {
    if (-1 < DebugLevel) {
      printk("For this chip, no specified channel switch function!\n");
      return;
    }
  }
  else {
    (**(code **)(iVar1 + 0x54))(param_1,param_2,param_3,param_4,param_5,param_6);
  }
  return;
}

