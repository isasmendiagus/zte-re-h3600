// module: mt7915.ko
// function: AsicEvaluateRxAnt @ 0x1306e0
// size: 444 bytes
//

void AsicEvaluateRxAnt(int param_1)

{
  int iVar1;
  
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
    return;
  }
  if ((*(int *)(param_1 + 0xa77bb4) == 1) &&
     ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)) {
    return;
  }
  if ((*(uint *)(param_1 + 0xa39f84) & 0x4140) != 0) {
    return;
  }
  iVar1 = IsHcAllSupportedBandsRadioOff();
  if (iVar1 != 0) {
    return;
  }
  if (*(byte *)(param_1 + 0x794ab8) != 0) {
    if (((&DAT_0036e600)[param_1] != '\0') && ((&DAT_00580018)[param_1] != '\0')) {
      return;
    }
    if ((1 < *(byte *)(param_1 + 0x794ab8)) &&
       (((&DAT_00581db0)[param_1] != '\0' && (*(char *)(param_1 + 0x7937c8) != '\0')))) {
      return;
    }
  }
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 == 2) {
    return;
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    if (*(short *)(param_1 + 0x285920) == 0) {
      return;
    }
    APAsicEvaluateRxAnt(param_1);
    return;
  }
  if (*(char *)(param_1 + 0x286285) != '\0') {
    return;
  }
  if (*(short *)(&DAT_00580010 + param_1) == 1) {
    return;
  }
  bbp_set_rxpath(param_1,"SetPartProfileParameters"[param_1 + 0x18] & 0xf);
  if ((*(uint *)(&DAT_0057ffbc + param_1) & 0x80) == 0) {
    return;
  }
  if ((uint)(*(int *)(param_1 + 0xa39e24) + *(int *)(param_1 + 0xa39e20) +
            *(int *)(param_1 + 0xa39e1c)) < 0x33) {
    RTMPSetTimer(param_1 + 0x829224,300);
    *(undefined1 *)(param_1 + 0x829221) = 1;
    return;
  }
  RTMPSetTimer(param_1 + 0x829224,0x14);
  *(undefined1 *)(param_1 + 0x829221) = 0;
  return;
}

