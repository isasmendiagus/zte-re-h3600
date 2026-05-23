// module: mt7915.ko
// function: NRRspTimeout @ 0x21f06c
// size: 180 bytes
//

void NRRspTimeout(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 auStack_19 [5];
  
  uVar1 = *(undefined1 *)(param_2 + 1);
  if (0 < DebugLevel) {
    printk("%s StaMac(%02x:%02x:%02x:%02x:%02x:%02x), MeasureReqToken=%d\n","NRRspTimeout",
           *(undefined1 *)(param_2 + 2),*(undefined1 *)(param_2 + 3),*(undefined1 *)(param_2 + 4),
           *(undefined1 *)(param_2 + 5),*(undefined1 *)(param_2 + 6),*(undefined1 *)(param_2 + 7),
           uVar1);
  }
  iVar2 = MeasureReqLookUp(param_1,uVar1);
  if (iVar2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s nr response entry not founded\n","NRRspTimeout");
    }
  }
  else {
    RTMPReleaseTimer(iVar2 + 0x14,auStack_19);
    MeasureReqDelete(param_1,uVar1);
  }
  return;
}

