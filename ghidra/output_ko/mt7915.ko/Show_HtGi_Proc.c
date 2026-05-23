// module: mt7915.ko
// function: Show_HtGi_Proc @ 0xd5cc4
// size: 124 bytes
//

undefined4 Show_HtGi_Proc(int *param_1,char *param_2,size_t param_3)

{
  int iVar1;
  uint uVar2;
  char *apcStack_1c [4];
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  apcStack_1c[0] = "GI_800";
  apcStack_1c[1] = "GI_400";
  apcStack_1c[2] = "GI_Unknown";
  if (iVar1 != 0) {
    uVar2 = wlan_config_get_ht_gi(iVar1);
    if (1 < uVar2) {
      uVar2 = 2;
    }
    snprintf(param_2,param_3,"\ti%s",apcStack_1c[uVar2]);
  }
  return 0;
}

