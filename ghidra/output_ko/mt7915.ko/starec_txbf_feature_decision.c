// module: mt7915.ko
// function: starec_txbf_feature_decision @ 0x88ffc
// size: 328 bytes
//

undefined4 starec_txbf_feature_decision(int param_1,int *param_2,uint *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = *(int *)(param_1 + 8);
  if (((param_2 == (int *)0x0) || (*param_2 == 0)) || (iVar1 = HcIsBfCapSupport(), iVar1 == 0)) {
    uVar3 = 0;
    goto LAB_00089024;
  }
  iVar1 = wlan_config_get_etxbf(param_1);
  if (((iVar1 == 1) || (iVar1 = wlan_config_get_etxbf(param_1), iVar1 == 2)) ||
     (iVar1 = wlan_config_get_itxbf(param_1), iVar1 == 1)) {
    if (*(int *)(param_1 + 0x14) != 1) {
      if (*(int *)(param_1 + 0x14) == 2) {
        if ((*(byte *)(iVar2 + 0x286294) & 3) != 3) goto LAB_000890cc;
        if ((*param_2 == 2 || *param_2 == 0x40001) &&
           (*(undefined1 *)(iVar2 + 0xa786f7) = 1, *(char *)(iVar2 + 0xa786f6) == '\0')) {
          *(undefined1 *)(iVar2 + 0xa786f6) = 1;
          uVar3 = 0x10;
          *(char *)(iVar2 + 0xa786f5) = (char)(short)param_2[0x38];
          goto LAB_00089078;
        }
      }
      goto LAB_00089074;
    }
    if (*param_2 != 0x20001) goto LAB_00089074;
LAB_000890cc:
    uVar3 = 0x10;
    *(undefined1 *)(iVar2 + 0xa786f7) = 0;
  }
  else {
LAB_00089074:
    uVar3 = 0;
  }
LAB_00089078:
  iVar2 = wlan_config_get_etxbf(param_1);
  if ((iVar2 == 1) || (iVar2 = wlan_config_get_etxbf(param_1), iVar2 == 3)) {
    uVar3 = uVar3 | 0x100000;
  }
LAB_00089024:
  *param_3 = *param_3 | uVar3;
  return 1;
}

