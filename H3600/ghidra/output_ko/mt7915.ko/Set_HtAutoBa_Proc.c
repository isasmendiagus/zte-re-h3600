// module: mt7915.ko
// function: Set_HtAutoBa_Proc @ 0xde468
// size: 140 bytes
//

undefined4 Set_HtAutoBa_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    return 0;
  }
  uVar1 = os_str_tol(param_2,0,10);
  wlan_config_set_ba_enable(iVar2,uVar1);
  SetCommonHtVht(param_1,iVar2);
  if (DebugLevel < 3) {
    return 1;
  }
  printk("Set_HtAutoBa_Proc::(HtAutoBa=%d)\n",uVar1);
  return 1;
}

