// module: mt7915.ko
// function: AutoChSelRelease @ 0x266e0
// size: 64 bytes
//

void AutoChSelRelease(undefined4 param_1)

{
  int iVar1;
  undefined1 uStack_9;
  
  iVar1 = HcGetAutoChCtrlbyBandIdx(param_1,0);
  RTMPReleaseTimer(iVar1 + 0x18,&uStack_9);
  iVar1 = HcGetAutoChCtrlbyBandIdx(param_1,1);
  RTMPReleaseTimer(iVar1 + 0x18,&uStack_9);
  return;
}

