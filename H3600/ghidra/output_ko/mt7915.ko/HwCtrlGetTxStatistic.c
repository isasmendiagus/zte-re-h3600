// module: mt7915.ko
// function: HwCtrlGetTxStatistic @ 0xaeb8c
// size: 148 bytes
//

undefined4 HwCtrlGetTxStatistic(int param_1,int param_2)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  puVar5 = *(undefined4 **)(param_2 + 8);
  uVar1 = *(ushort *)(puVar5 + 1);
  uVar2 = HcGetMaxStaNum();
  if ((((uVar1 < uVar2) &&
       (iVar4 = (uint)*(ushort *)(puVar5 + 1) * 0x14c0 + param_1, *(int *)(iVar4 + 0xa1d20) != 0))
      && (*(int *)(iVar4 + 0xa1d28) != 0)) &&
     (uVar3 = HcGetBandByWdev(),
     *(char *)(param_1 + (uint)*(ushort *)(iVar4 + 0xa1e02) * 0x620 + 0x2fa88) == '\x02')) {
    mt_cmd_get_sta_tx_statistic(param_1,*(undefined2 *)(puVar5 + 1),uVar3,*puVar5);
  }
  return 0;
}

