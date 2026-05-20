// module: mt7915.ko
// function: StaQuickResponeForRateUpExec @ 0x1da2d0
// size: 136 bytes
//

void StaQuickResponeForRateUpExec(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  piVar3 = (int *)(param_2 + 0xa31e0);
  (&DAT_00580cc8)[param_2] = 0;
  for (uVar4 = 1; uVar1 = HcGetMaxStaNum(param_2), uVar4 < uVar1; uVar4 = uVar4 + 1) {
    if (((*piVar3 != 0) && (iVar2 = RTMPCheckEntryEnableAutoRateSwitch(param_2,piVar3), iVar2 != 0))
       && (iVar2 = hc_get_hif_type(*(undefined4 *)(param_2 + 0xa797a0)), iVar2 == 2)) {
      QuickResponeForRateAdaptMT(param_2,uVar4 & 0xff);
    }
    piVar3 = piVar3 + 0x530;
  }
  return;
}

