// module: mt7915.ko
// function: QBSS_LoadIsAlarmIssued @ 0x26d94
// size: 28 bytes
//

undefined1 QBSS_LoadIsAlarmIssued(void)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = HcGetQloadCtrl();
  uVar1 = *(undefined1 *)(iVar2 + 0xcc);
  *(undefined1 *)(iVar2 + 0xcc) = 0;
  return uVar1;
}

