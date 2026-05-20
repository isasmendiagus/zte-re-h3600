// module: mt7915.ko
// function: Set_HtStbc_Proc @ 0xde000
// size: 160 bytes
//

undefined4 Set_HtStbc_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if ((iVar1 != 0) && ((iVar2 = os_str_tol(param_2,0,10), iVar2 == 1 || (iVar2 == 0)))) {
    wlan_config_set_ht_stbc(iVar1,iVar2);
    SetCommonHtVht(param_1,iVar1);
    if (DebugLevel < 3) {
      return 1;
    }
    uVar3 = wlan_config_get_ht_stbc(iVar1);
    printk("Set_Stbc_Proc::(HtStbc=%d)\n",uVar3);
    return 1;
  }
  return 0;
}

