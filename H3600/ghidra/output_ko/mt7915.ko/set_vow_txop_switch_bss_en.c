// module: mt7915.ko
// function: set_vow_txop_switch_bss_en @ 0x44110
// size: 196 bytes
//

undefined4 set_vow_txop_switch_bss_en(int param_1,char *param_2)

{
  int iVar1;
  undefined4 local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u",local_14);
  if (iVar1 != 0) {
    *(char *)(param_1 + 0xa7a2eb) = (char)local_14[0];
    iVar1 = vow_set_feature_all(param_1);
    if (DebugLevel < 0) {
      if (iVar1 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: set %u.\n","set_vow_txop_switch_bss_en",local_14[0]);
      if (iVar1 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_txop_switch_bss_en");
      }
    }
  }
  return 0;
}

