// module: mt7915.ko
// function: WrapDfsRadarDetectStart @ 0x235bb8
// size: 320 bytes
//

void WrapDfsRadarDetectStart(int param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 auStack_2b [15];
  
  if (param_2 == 0) {
    return;
  }
  if (*(byte *)(param_2 + 0x1a) < 0xf) {
    return;
  }
  iVar2 = hc_radio_query_by_wdev(param_2,auStack_2b);
  if ((iVar2 == 0) && (iVar2 = *(int *)(param_2 + 0x3fe4), iVar2 != 0)) {
    iVar3 = HcGetBandByWdev(param_2);
    iVar4 = param_1 + 0x795000;
    iVar5 = iVar4 + iVar3;
    uVar1 = RadarChannelCheck(param_1,*(undefined1 *)(iVar5 + 0x130));
    *(undefined1 *)(iVar5 + 0x3e1) = uVar1;
    if (*(char *)(iVar5 + 0x134) == '\x06') {
      uVar1 = RadarChannelCheck(param_1,*(undefined1 *)(param_1 + 0x795131));
      *(undefined1 *)(param_1 + 0x7953e2) = uVar1;
    }
    if ((*(char *)(iVar4 + iVar3 + 0x134) == '\x03') &&
       (*(undefined1 *)(param_1 + 0x7953e2) = *(undefined1 *)(param_1 + 0x7953e1),
       *(byte *)(param_1 + 0x795132) - 0x24 < 0xd)) {
      *(undefined1 *)(param_1 + 0x7953e2) = 1;
    }
    if ((0 < DebugLevel) &&
       (printk("[%s]: DfsChBand[0]: %d, DfsChBand[1]: %d\n","WrapDfsRadarDetectStart",
               *(undefined1 *)(param_1 + 0x7953e1),*(undefined1 *)(param_1 + 0x7953e2)),
       2 < DebugLevel)) {
      printk("[%s] BandIdx: %d, BW: %d, RDMode: %d\n","WrapDfsRadarDetectStart",iVar3,
             *(undefined1 *)(iVar4 + iVar3 + 0x134),*(undefined1 *)(iVar2 + 4));
    }
    DfsRadarDetectStart(param_1,param_1 + 0x795130,param_2);
  }
  return;
}

