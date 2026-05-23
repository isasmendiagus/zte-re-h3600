// module: mt7915.ko
// function: APMlmeDynamicTxRateSwitching @ 0x1d9f9c
// size: 276 bytes
//

void APMlmeDynamicTxRateSwitching(int param_1)

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
  down_interruptible(param_1 + 0x285d58);
  piVar3 = (int *)(param_1 + 0xa31e0);
  for (uVar4 = 1; uVar1 = HcGetMaxStaNum(param_1), uVar4 < uVar1; uVar4 = uVar4 + 1) {
    iVar2 = *piVar3;
    if (((iVar2 != 0) &&
        ((((iVar2 != 0x20001 && (iVar2 != 2)) && (iVar2 != 0x40001)) || (piVar3[0x3f] == 2)))) &&
       ((iVar2 = RTMPCheckEntryEnableAutoRateSwitch(param_1,piVar3), iVar2 != 0 &&
        (iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0)), iVar2 == 2)))) {
      DynamicTxRateSwitchingAdaptMT(param_1,uVar4 & 0xff);
    }
    piVar3 = piVar3 + 0x530;
  }
  "auth_fsm_reset"[param_1 + 6] = '\0';
  up(param_1 + 0x285d58);
  return;
}

