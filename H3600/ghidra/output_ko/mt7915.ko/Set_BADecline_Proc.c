// module: mt7915.ko
// function: Set_BADecline_Proc @ 0xdd694
// size: 112 bytes
//

undefined4 Set_BADecline_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *param_1;
  uVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar3 + 0x3c),*(undefined4 *)(iVar3 + 0x38),iVar3,
                     param_4);
  uVar1 = os_str_tol(param_2,0,10);
  wlan_config_set_ba_decline(uVar2,uVar1);
  if (2 < DebugLevel) {
    uVar2 = wlan_config_get_ba_decline(uVar2);
    printk("Set_BADecline_Proc::(BADecline=%d)\n",uVar2);
  }
  return 1;
}

