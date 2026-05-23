// module: mt7915.ko
// function: wlan_operate_set_support_ch_width_set @ 0x107a00
// size: 84 bytes
//

undefined4
wlan_operate_set_support_ch_width_set
          (int param_1,byte param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): can\'t find wlan opeate!\n","wlan_operate_set_support_ch_width_set",param_3,
             DebugLevel,param_4);
    }
  }
  else {
    iVar1 = *(int *)(param_1 + 0xb14);
    if (iVar1 != 0) {
      *(byte *)(iVar1 + 0x36) = *(byte *)(iVar1 + 0x36) & 0xfd | (param_2 & 1) << 1;
    }
  }
  return 0;
}

