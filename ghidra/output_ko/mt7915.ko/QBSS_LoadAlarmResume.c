// module: mt7915.ko
// function: QBSS_LoadAlarmResume @ 0x26d5c
// size: 20 bytes
//

void QBSS_LoadAlarmResume(void)

{
  int iVar1;
  
  iVar1 = HcGetQloadCtrl();
  *(undefined1 *)(iVar1 + 0xc0) = 0;
  return;
}

