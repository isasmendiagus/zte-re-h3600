// module: mt7915.ko
// function: Show_HtBw_Proc @ 0xd5bdc
// size: 88 bytes
//

undefined4 Show_HtBw_Proc(int *param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  char *__format;
  int iVar1;
  
  iVar1 = *param_1;
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar1 + 0x3c),*(undefined4 *)(iVar1 + 0x38),iVar1,
                     param_4);
  if (iVar1 != 0) {
    iVar1 = wlan_config_get_ht_bw();
    if (iVar1 == 1) {
      __format = "\t40 MHz";
    }
    else {
      __format = "\t20 MHz";
    }
    snprintf(param_2,param_3,__format);
  }
  return 0;
}

