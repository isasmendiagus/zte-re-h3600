// module: mt7915.ko
// function: Show_HtExtcha_Proc @ 0xd5d88
// size: 144 bytes
//

undefined4 Show_HtExtcha_Proc(int *param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = *param_1;
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar1 + 0x3c),*(undefined4 *)(iVar1 + 0x38),iVar1,
                     param_4);
  if (iVar1 != 0) {
    iVar1 = wlan_config_get_ext_cha();
    if (iVar1 == 1) {
      snprintf(param_2,param_3,"\tAbove");
      return 0;
    }
    if (iVar1 == 3) {
      snprintf(param_2,param_3,"\tBelow");
      return 0;
    }
  }
  snprintf(param_2,param_3,"\tUnknow Value(%u)");
  return 0;
}

