// module: mt7915.ko
// function: Set_HtMpduDensity_Proc @ 0xde168
// size: 160 bytes
//

undefined4 Set_HtMpduDensity_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar2 = os_str_tol(param_2,0,10);
  if (iVar1 == 0) {
    return 0;
  }
  if (uVar2 < 8) {
    uVar2 = uVar2 & 0xff;
  }
  else {
    uVar2 = 0;
  }
  wlan_config_set_min_mpdu_start_space(iVar1,uVar2);
  SetCommonHtVht(param_1,0);
  uVar3 = wlan_config_get_min_mpdu_start_space(iVar1);
  if (2 < DebugLevel) {
    printk("Set_HtMpduDensity_Proc::(HtMpduDensity=%d)\n",uVar3);
    return 1;
  }
  return 1;
}

