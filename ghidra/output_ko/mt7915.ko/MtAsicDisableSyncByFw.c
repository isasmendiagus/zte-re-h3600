// module: mt7915.ko
// function: MtAsicDisableSyncByFw @ 0x199a78
// size: 140 bytes
//

void MtAsicDisableSyncByFw(int param_1,uint param_2)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(param_1 + 8);
  do {
    piVar2 = piVar2 + 1;
    iVar1 = *piVar2;
    if ((iVar1 != 0) && (*(byte *)(iVar1 + 0x29) == param_2)) goto LAB_00199aa8;
  } while (piVar2 != (int *)(param_1 + 0x1a8));
  if (iVar1 == 0) {
    return;
  }
LAB_00199aa8:
  if (*(int *)(iVar1 + 0x990) != 0) {
    *(undefined4 *)(iVar1 + 0x990) = 1;
    CmdSetSyncModeByBssInfoUpdate(param_1,iVar1 + 0x98c);
    return;
  }
  if (DebugLevel < 2) {
    return;
  }
  printk("%s: BssInfo idx (%d) is INIT currently!!!\n","MtAsicDisableSyncByFw",
         *(undefined1 *)(iVar1 + 0x999));
  return;
}

