// module: mt7915.ko
// function: WscScanDoneCheckTimeOutAction @ 0x1e522c
// size: 244 bytes
//

void WscScanDoneCheckTimeOutAction(undefined4 param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined1 auStack_19 [5];
  
  if (DebugLevel < 1) {
    if (param_2 == 0) {
      return;
    }
  }
  else {
    printk("-----> WscScanDoneCheckTimeOutAction\n");
    if (param_2 == 0) goto LAB_001e528c;
  }
  iVar3 = *(int *)(param_2 + 0x29e8);
  bVar1 = *(byte *)(param_2 + 0x1c54);
  uVar2 = bVar1 & 0xf;
  if (iVar3 != 0) {
    *(undefined1 *)(param_2 + 0x28ac) = 0;
    RTMPCancelTimer(param_2 + 0x28b0,auStack_19);
    if ((bVar1 & 0xf) == 0 || uVar2 == 1) {
      MlmeEnqueueWithWdev(iVar3,4,9,0,0,uVar2,&DAT_0036db58 + iVar3 + uVar2 * 0x2137b0);
      RtmpOsMlmeUp(iVar3 + 0x286298);
    }
  }
LAB_001e528c:
  if (0 < DebugLevel) {
    printk("<----- WscScanDoneCheckTimeOutAction\n");
  }
  return;
}

