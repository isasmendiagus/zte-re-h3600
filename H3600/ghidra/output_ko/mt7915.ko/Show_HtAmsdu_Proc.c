// module: mt7915.ko
// function: Show_HtAmsdu_Proc @ 0xd5ea4
// size: 104 bytes
//

undefined4 Show_HtAmsdu_Proc(int *param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = *param_1;
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar1 + 0x3c),*(undefined4 *)(iVar1 + 0x38),iVar1,
                     param_4);
  if (iVar1 == 0) {
    pcVar2 = "FALSE";
  }
  else {
    iVar1 = wlan_config_get_amsdu_en();
    pcVar2 = "TRUE";
    if (iVar1 == 0) {
      pcVar2 = "FALSE";
    }
  }
  snprintf(param_2,param_3,"\t%s",pcVar2);
  return 0;
}

