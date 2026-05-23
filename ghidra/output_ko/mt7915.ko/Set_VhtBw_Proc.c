// module: mt7915.ko
// function: Set_VhtBw_Proc @ 0xdf70c
// size: 284 bytes
//

undefined4 Set_VhtBw_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  
  iVar3 = *param_1;
  iVar3 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar3 + 0x3c),*(undefined4 *)(iVar3 + 0x38),iVar3,
                     param_4);
  if (iVar3 == 0) {
    return 0;
  }
  uVar1 = os_str_tol(param_2,0,10);
  if (0xe < *(byte *)(iVar3 + 0x1a)) {
    iVar3 = HcGetBandByWdev(iVar3);
    if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
      iVar5 = 0;
      uVar6 = uVar1 & 0xff;
      if (3 < uVar1) {
        uVar6 = 0;
      }
      piVar4 = param_1 + 0xadc92;
      uVar1 = 1;
      do {
        iVar2 = HcGetBandByWdev(piVar4);
        if (iVar2 == iVar3) {
          wlan_config_set_vht_bw(piVar4,uVar6);
          uVar1 = uVar6;
          if ((*(ushort *)(piVar4 + 6) & 0x20) != 0) {
            wlan_operate_set_vht_bw(piVar4,uVar6);
          }
        }
        iVar5 = iVar5 + 1;
        piVar4 = piVar4 + 0x160d;
      } while (iVar5 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      goto LAB_000df754;
    }
  }
  uVar1 = 1;
LAB_000df754:
  if (DebugLevel < 3) {
    return 1;
  }
  printk("Set_VhtBw_Proc::(VHT_BW=%d)\n",uVar1);
  return 1;
}

