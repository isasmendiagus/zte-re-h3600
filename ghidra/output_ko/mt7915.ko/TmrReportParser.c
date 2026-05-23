// module: mt7915.ko
// function: TmrReportParser @ 0x1d7c34
// size: 692 bytes
//

void TmrReportParser(int param_1,undefined2 *param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar4 = *(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10);
  bVar1 = *(byte *)((int)param_2 + 5);
  if (iVar4 == 0) {
    return;
  }
  if (*(char *)(iVar4 + 1) == '\0') {
    return;
  }
  *(undefined4 *)(iVar4 + 4) = param_4;
  tmr_raw_dump("TMR RAW data: ",param_2,0x1c);
  uVar5 = (uint)*(byte *)((int)param_2 + 3);
  if ((*(byte *)((int)param_2 + 3) & 0x10) == 0) {
    iVar4 = (uint)(ushort)param_2[0xd] - (uint)(ushort)param_2[0xc];
    iVar3 = *(int *)(param_2 + 10) - *(int *)(param_2 + 8);
  }
  else {
    iVar4 = (uint)(ushort)param_2[0xc] - (uint)(ushort)param_2[0xd];
    iVar3 = *(int *)(param_2 + 8) - *(int *)(param_2 + 10);
  }
  if (0 < DebugLevel) {
    printk("DWORD_0: ByteCnt=%d, NC=%d, TMF=%d, ToaVld=%d, TodVld=%d, tod_fine=%x\n",*param_2,
           ((uint)*(byte *)(param_2 + 1) << 0x1d) >> 0x1f,
           ((uint)*(byte *)(param_2 + 1) << 0x1c) >> 0x1f,(uVar5 << 0x1d) >> 0x1f,
           (uVar5 << 0x1c) >> 0x1f,bVar1 & 0x3f);
    uVar5 = (uint)*(byte *)((int)param_2 + 3);
  }
  if ((uVar5 & 0x10) == 0) {
    iVar2 = *(int *)(param_2 + 10);
    if (*(int *)(param_2 + 10) == DAT_005f4920) {
      if (DebugLevel < 3) {
        return;
      }
      printk("##### latest TOA is same as last time\n");
      return;
    }
  }
  else {
    uVar5 = (uint)(ushort)param_2[5];
    if (uVar5 == _LANCHOR0) {
      if (DebugLevel < 1) {
        _LANCHOR0 = uVar5;
        return;
      }
      printk("##### latest sn is same as last time\n");
      uVar5 = (uint)(ushort)param_2[5];
    }
    if (DebugLevel < 1) {
      _LANCHOR0 = uVar5;
      return;
    }
    _LANCHOR0 = uVar5;
    printk("TYPE=%x, SUB_TYPE=%x, SN=%x\n",((uint)*(byte *)(param_2 + 1) << 0x1a) >> 0x1e,
           (*(byte *)((int)param_2 + 3) & 3) << 2 | *(byte *)(param_2 + 1) >> 6);
    uVar5 = *(uint *)(param_2 + 6);
    if (DebugLevel < 1) {
      return;
    }
    printk("Readable TA = %02x:%02x:%02x:%02x:%02x:%02x\n",param_2[4] & 0xff,(ushort)param_2[4] >> 8
           ,uVar5 & 0xff,uVar5 >> 8 & 0xff,uVar5 >> 0x10 & 0xff,uVar5 >> 0x18);
    iVar2 = DAT_005f4920;
  }
  DAT_005f4920 = iVar2;
  if ((((0 < DebugLevel) && (printk("TOAECalibrationResult=0x%X\n",param_4), 0 < DebugLevel)) &&
      (printk("DWORD_4: TOD[0:31]=0x%x\n",*(undefined4 *)(param_2 + 8)), 0 < DebugLevel)) &&
     (((printk("DWORD_6: TOD[32:47]=0x%x\n",param_2[0xc]), 0 < DebugLevel &&
       (printk("DWORD_5: TOA[0:31]=0x%x\n",*(undefined4 *)(param_2 + 10)), 0 < DebugLevel)) &&
      (printk("DWORD_6: TOA[32:47]=0x%x\n",param_2[0xd]), 0 < DebugLevel)))) {
    printk("TMR Report: ir = %d, delta_high = %d, delta_low = %d\n\n",
           ((uint)*(byte *)((int)param_2 + 3) << 0x1b) >> 0x1f,iVar4,iVar3);
    return;
  }
  return;
}

