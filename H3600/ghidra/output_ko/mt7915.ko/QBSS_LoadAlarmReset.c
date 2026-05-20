// module: mt7915.ko
// function: QBSS_LoadAlarmReset @ 0x26c2c
// size: 64 bytes
//

void QBSS_LoadAlarmReset(int param_1)

{
  int iVar1;
  
  iVar1 = HcGetQloadCtrl();
  *(undefined1 *)(iVar1 + 0xcc) = 0;
  *(undefined1 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
  *(undefined1 *)(iVar1 + 0xc0) = 0;
  FUN_00026bfc(param_1,*(undefined2 *)(&DAT_00794c50 + param_1));
  return;
}

