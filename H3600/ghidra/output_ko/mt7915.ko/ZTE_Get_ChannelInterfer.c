// module: mt7915.ko
// function: ZTE_Get_ChannelInterfer @ 0x1577ec
// size: 192 bytes
//

uint ZTE_Get_ChannelInterfer(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar3 = HcGetAmountOfBand();
  iVar5 = *param_1;
  iVar5 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar5 + 0x3c),*(undefined4 *)(iVar5 + 0x38),iVar5,
                     param_4);
  uVar4 = 0;
  if (iVar5 != 0) {
    uVar4 = HcGetBandByWdev();
  }
  if (uVar3 <= uVar4) {
    return 0;
  }
  sVar1 = (short)uVar4;
  iVar5 = param_1[(int)(&UNK_0029f0c6 + sVar1)] * -0x2e48e8a7;
  uVar3 = (uint)param_1[(int)(&UNK_0029f0c6 + sVar1)] / 10000;
  if (9 < uVar3) {
    uVar2 = param_1[(int)("cmd_txbf_en_dynsnd_intr" + sVar1 + 2)];
    if ((uint)param_1[(int)("cmd_txbf_en_dynsnd_intr" + sVar1 + 2)] < 100000) {
      uVar2 = param_1[(int)("cmd_txbf_en_dynsnd_intr" + sVar1)];
    }
    if (uVar2 < 100000) {
      uVar3 = ZTE_Get_ChannelUtilization(param_1,uVar4,iVar5);
    }
    else {
      iVar5 = ZTE_Get_ChannelUtilization(param_1,uVar4,iVar5);
      uVar3 = iVar5 - uVar3 & ~((int)(iVar5 - uVar3) >> 0x1f);
    }
    if (99 < uVar3) {
      return 100;
    }
  }
  return uVar3;
}

