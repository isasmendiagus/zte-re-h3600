// module: mt7915.ko
// function: AsicRxAntEvalTimeout @ 0x13089c
// size: 420 bytes
//

void AsicRxAntEvalTimeout(undefined4 param_1,int param_2)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined1 uVar4;
  char cVar5;
  
  if ((*(uint *)(param_2 + 0xa3ac14) & 1) != 0) {
    return;
  }
  if ((*(int *)(param_2 + 0xa77bb4) == 1) &&
     ((*(uint *)(*(int *)(param_2 + 0xa77bb8) + 0x4e0) & 1) != 0)) {
    return;
  }
  if ((*(uint *)(param_2 + 0xa39f84) & 0x140) != 0) {
    return;
  }
  iVar3 = IsHcAllSupportedBandsRadioOff(param_2);
  if (iVar3 != 0) {
    return;
  }
  if (*(byte *)(param_2 + 0x794ab8) != 0) {
    if (((&DAT_0036e600)[param_2] != '\0') && ((&DAT_00580018)[param_2] != '\0')) {
      return;
    }
    if (((1 < *(byte *)(param_2 + 0x794ab8)) && ((&DAT_00581db0)[param_2] != '\0')) &&
       (*(char *)(param_2 + 0x7937c8) != '\0')) {
      return;
    }
  }
  if (*(char *)(param_2 + 0x286285) == '\x01') {
    APAsicRxAntEvalTimeout(param_2);
    return;
  }
  if (*(char *)(param_2 + 0x286285) != '\0') {
    return;
  }
  if (*(short *)(&DAT_00580010 + param_2) == 1) {
    return;
  }
  if (*(char *)(param_2 + 0x829221) == '\x01') {
    cVar1 = (&DAT_00580d20)[param_2];
    cVar2 = (&DAT_00580d21)[param_2];
    cVar5 = (&DAT_00580d22)[param_2];
  }
  else {
    cVar1 = (&DAT_00580d24)[param_2];
    cVar2 = (&DAT_00580d25)[param_2];
    cVar5 = (&DAT_00580d26)[param_2];
  }
  if (("SetPartProfileParameters"[param_2 + 0x18] & 0xfU) == 3) {
    iVar3 = (int)cVar2;
    if ((int)cVar2 < (int)cVar1) {
      iVar3 = (int)cVar1;
    }
    uVar4 = 3;
    if (cVar5 + 0x14 < iVar3) {
LAB_00130a08:
      uVar4 = 2;
      *(undefined1 *)(param_2 + 0x829220) = 2;
      goto LAB_001309c8;
    }
  }
  else {
    if (("SetPartProfileParameters"[param_2 + 0x18] & 0xfU) != 2) {
      uVar4 = *(undefined1 *)(param_2 + 0x829220);
      goto LAB_001309c8;
    }
    if ((int)cVar1 <= cVar2 + 0x14) goto LAB_00130a08;
    uVar4 = 1;
  }
  *(undefined1 *)(param_2 + 0x829220) = uVar4;
LAB_001309c8:
  bbp_set_rxpath(param_2,uVar4);
  return;
}

