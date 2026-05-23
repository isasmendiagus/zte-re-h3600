// module: mt7915.ko
// function: Show_HtMpduDensity_Proc @ 0xd5e18
// size: 72 bytes
//

undefined4 Show_HtMpduDensity_Proc(int *param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar2 + 0x3c),*(undefined4 *)(iVar2 + 0x38),iVar2,
                     param_4);
  uVar1 = 0;
  if (iVar2 != 0) {
    uVar1 = wlan_config_get_min_mpdu_start_space();
  }
  snprintf(param_2,param_3,"\t%u",uVar1);
  return 0;
}

