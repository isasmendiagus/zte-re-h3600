// module: mt7915.ko
// function: Set_HtMIMOPSmode_Proc @ 0xde748
// size: 156 bytes
//

undefined4 Set_HtMIMOPSmode_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    return 0;
  }
  uVar2 = os_str_tol(param_2,0,10);
  if (2 < uVar2) {
    uVar2 = 3;
  }
  wlan_config_set_mmps(iVar1,uVar2 & 0xff);
  SetCommonHtVht(param_1,iVar1);
  uVar3 = wlan_config_get_mmps(iVar1);
  if (DebugLevel < 3) {
    return 1;
  }
  printk("Set_HtMIMOPSmode_Proc::(MIMOPS mode=%d)\n",uVar3);
  return 1;
}

