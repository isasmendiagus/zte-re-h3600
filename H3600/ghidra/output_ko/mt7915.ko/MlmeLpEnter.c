// module: mt7915.ko
// function: MlmeLpEnter @ 0x12ca7c
// size: 160 bytes
//

void MlmeLpEnter(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    return;
  }
  iVar2 = param_1[0xa18a0];
  bVar3 = iVar2 != 0;
  if (iVar2 != 1) {
    bVar3 = iVar2 != 4;
  }
  if (bVar3 && (iVar2 != 1 && iVar2 != 5)) {
    return;
  }
  if ((param_1[0xa5b19] & 0xffffU) != 0x7622) {
    MTMlmeLpEnter(param_1,iVar1,param_1[0xa5b19] & 0xffffU,param_4);
    return;
  }
  if (*(char *)((int)param_1 + 0x286285) != '\0') {
    MlmeRadioOff(param_1,iVar1,0x7622,param_4);
    return;
  }
  MSTAStop(param_1,iVar1);
  MlmeRadioOff(param_1,iVar1);
  return;
}

