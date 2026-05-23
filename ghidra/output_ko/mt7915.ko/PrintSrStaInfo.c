// module: mt7915.ko
// function: PrintSrStaInfo @ 0x16d110
// size: 360 bytes
//

void PrintSrStaInfo(undefined2 *param_1,undefined4 param_2)

{
  uint uVar1;
  char *apcStack_44 [4];
  char *pcStack_34;
  char *pcStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  char *local_24;
  
  uVar1 = (uint)(ushort)param_1[5];
  if (uVar1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = __aeabi_idiv((uVar1 - (ushort)param_1[4]) * 1000,uVar1);
  }
  apcStack_44[0] = "AUTO";
  apcStack_44[1] = "FIXED";
  pcStack_34 = "Invailid";
  pcStack_30 = "Not Stable";
  puStack_2c = &DAT_002f3b1c;
  puStack_28 = &DAT_002f3b24;
  local_24 = "Timeout";
  apcStack_44[2] = "Stable";
  apcStack_44[3] = "Active";
  if ((((-1 < DebugLevel) &&
       (printk("        STA %2d\n        u2WlanId       = %d, u1Mode       = %s,  u1State = %s\n",
               param_2,*param_1,apcStack_44[*(byte *)(param_1 + 1)],
               apcStack_44[*(byte *)((int)param_1 + 3) + 4]), -1 < DebugLevel)) &&
      (printk("        u1SrRateOffset = %d, u1SrRaTryCnt = %x, u1SrRaRound = %x, u1SrRaState = %s\n"
              ,*(undefined1 *)(param_1 + 2),*(undefined1 *)((int)param_1 + 5),
              *(undefined1 *)(param_1 + 3),apcStack_44[*(byte *)((int)param_1 + 7) + 2]),
      -1 < DebugLevel)) &&
     (printk("        u2SrSucCnt  = %x, u2SrTtlTxCnt = %x, PER = %d.%1d%%\n",param_1[4],param_1[5],
             uVar1 / 10,uVar1 % 10), -1 < DebugLevel)) {
    printk("        u4Score = %x, u1StateBadQuota = %x, u1SrRate = %x\n",
           *(undefined4 *)(param_1 + 6),*(undefined1 *)(param_1 + 8),
           *(undefined1 *)((int)param_1 + 0x11));
    return;
  }
  return;
}

