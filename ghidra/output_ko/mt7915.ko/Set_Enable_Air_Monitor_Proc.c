// module: mt7915.ko
// function: Set_Enable_Air_Monitor_Proc @ 0x3476c
// size: 208 bytes
//

undefined4
Set_Enable_Air_Monitor_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *param_1;
  iVar3 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar3 + 0x3c),*(undefined4 *)(iVar3 + 0x38),iVar3,
                     param_4);
  if (2 < DebugLevel) {
    printk("--> %s()\n","Set_Enable_Air_Monitor_Proc");
  }
  if (iVar3 != 0) {
    uVar1 = simple_strtol(param_2,0,10);
    uVar2 = HcGetBandByWdev(iVar3);
    asic_set_air_mon_enable(param_1,uVar1,uVar2);
    if (DebugLevel < 3) {
      return 1;
    }
    printk("<-- %s()\n","Set_Enable_Air_Monitor_Proc");
    return 1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("wdev is NULL\n");
  return 0;
}

