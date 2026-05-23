// module: mt7915.ko
// function: MlmeDynamicTxRateSwitching @ 0x1da15c
// size: 372 bytes
//

void MlmeDynamicTxRateSwitching(int param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
    return;
  }
  if ((*(int *)(param_1 + 0xa77bb4) == 1) &&
     ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)) {
    return;
  }
  if ((*(char *)(param_1 + 0x794ab8) != '\0') &&
     ((((&DAT_0036e600)[param_1] != '\0' && ((&DAT_00580018)[param_1] != '\0')) ||
      ((*(char *)(param_1 + 0x794ab8) != '\x01' &&
       (((&DAT_00581db0)[param_1] != '\0' && (*(char *)(param_1 + 0x7937c8) != '\0')))))))) {
    if (3 < DebugLevel) {
      printk("%s(%d): H/W in PM4, return\n","MlmeDynamicTxRateSwitching",0x2d6);
      return;
    }
    return;
  }
  piVar3 = (int *)(param_1 + 0xa31e0);
  down_interruptible(param_1 + 0x285d58);
  for (uVar4 = 1; uVar1 = HcGetMaxStaNum(param_1), uVar4 < uVar1; uVar4 = uVar4 + 1) {
    if (((*piVar3 != 0) && (iVar2 = RTMPCheckEntryEnableAutoRateSwitch(param_1,piVar3), iVar2 != 0))
       && (iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0)), iVar2 == 2)) {
      DynamicTxRateSwitchingAdaptMT(param_1,uVar4 & 0xff);
    }
    piVar3 = piVar3 + 0x530;
  }
  "auth_fsm_reset"[param_1 + 6] = '\0';
  up(param_1 + 0x285d58);
  return;
}

