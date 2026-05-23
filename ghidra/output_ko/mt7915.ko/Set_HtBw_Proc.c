// module: mt7915.ko
// function: Set_HtBw_Proc @ 0xddc8c
// size: 296 bytes
//

undefined4 Set_HtBw_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  iVar4 = *param_1;
  iVar4 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar4 + 0x3c),*(undefined4 *)(iVar4 + 0x38),iVar4,
                     param_4);
  if (iVar4 == 0) {
    return 0;
  }
  iVar1 = os_str_tol(param_2,0,10);
  iVar6 = 0;
  iVar4 = HcGetBandByWdev(iVar4);
  *(undefined1 *)((int)param_1 + iVar4 + 0x795688) = 0;
  __memzero(param_1 + iVar4 * 2 + 0x1e55a3,8);
  if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
    piVar5 = param_1 + 0xadc92;
    do {
      iVar2 = HcGetBandByWdev(piVar5);
      if (iVar2 == iVar4) {
        if (iVar1 == 1) {
          wlan_config_set_ht_bw(piVar5,1);
          uVar3 = wlan_operate_get_ext_cha(piVar5);
          wlan_operate_set_ht_bw(piVar5,1,uVar3);
        }
        else {
          if (iVar1 != 0) {
            return 0;
          }
          wlan_config_set_ht_bw(piVar5,0);
          wlan_operate_set_ht_bw(piVar5,0,0);
        }
        SetCommonHtVht(param_1,piVar5);
      }
      iVar6 = iVar6 + 1;
      piVar5 = piVar5 + 0x160d;
    } while (iVar6 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
  }
  return 1;
}

