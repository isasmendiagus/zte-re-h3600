// module: mt7915.ko
// function: MtAsicEnableBssSyncByFw @ 0x199b08
// size: 140 bytes
//

void MtAsicEnableBssSyncByFw(int param_1,undefined4 param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(param_1 + 8);
  do {
    piVar1 = piVar1 + 1;
    iVar2 = *piVar1;
    if ((iVar2 != 0) && (*(byte *)(iVar2 + 0x29) == param_3)) goto LAB_00199b38;
  } while (piVar1 != (int *)(param_1 + 0x1a8));
  if (iVar2 == 0) {
    return;
  }
LAB_00199b38:
  if (*(int *)(iVar2 + 0x990) != 0) {
    *(undefined4 *)(iVar2 + 0x990) = 2;
    CmdSetSyncModeByBssInfoUpdate(param_1,iVar2 + 0x98c);
    return;
  }
  if (DebugLevel < 2) {
    return;
  }
  printk("%s: BssInfo idx (%d) is INIT currently!!!\n","MtAsicEnableBssSyncByFw",
         *(undefined1 *)(iVar2 + 0x999));
  return;
}

