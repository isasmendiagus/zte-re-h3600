// module: mt7915.ko
// function: ApCliRTMPSendPsPollFrame @ 0x128d80
// size: 288 bytes
//

void ApCliRTMPSendPsPollFrame(int param_1,int param_2)

{
  int iVar1;
  byte local_30;
  byte local_2f;
  ushort local_2e;
  undefined4 local_2c;
  undefined2 local_28;
  undefined4 local_26;
  undefined2 local_22;
  
  param_2 = param_2 * 0x2137b0;
  iVar1 = MacTableLookup(param_1,param_1 + param_2 + 0x36db79);
  if (iVar1 != 0) {
    if (((&DAT_0036e3e0)[param_1 + param_2] != '\x02') &&
       (*(char *)(param_1 + (uint)*(ushort *)(iVar1 + 0xe0) * 0x620 + 0x2f762) != '\x02')) {
      __memzero(&local_30,0x10);
      iVar1 = param_1 + param_2 + 0x371c90;
      local_2c = *(undefined4 *)(iVar1 + 2);
      local_26 = *(undefined4 *)(&DAT_0036db70 + param_1 + param_2 + 3);
      local_28 = *(undefined2 *)(iVar1 + 6);
      local_22 = *(undefined2 *)(&DAT_0036db70 + param_1 + param_2 + 7);
      local_2e = ~((ushort)~(ushort)(((uint)*(ushort *)(&DAT_00371cc2 + param_1 + param_2) << 0x12)
                                    >> 0x10) >> 2);
      local_2f = local_2f | 0x10;
      local_30 = local_30 & 3 | 0xa4;
      hif_kickout_nullframe_tx(param_1,0,&local_30);
      return;
    }
  }
  return;
}

