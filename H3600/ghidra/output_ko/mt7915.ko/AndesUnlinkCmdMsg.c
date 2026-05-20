// module: mt7915.ko
// function: AndesUnlinkCmdMsg @ 0x1a47e0
// size: 120 bytes
//

void AndesUnlinkCmdMsg(int param_1)

{
  int iVar1;
  undefined1 auStack_14 [8];
  
  iVar1 = AndesGetSpinLock(*(int *)(param_1 + 0x1c) + 0xa7849c);
  if (iVar1 != 0) {
    OS_SPIN_LOCK_IRQSAVE(iVar1,auStack_14);
    if (param_1 != 0) {
      if (*(int *)(param_1 + 0x48) != 0) {
        *(undefined4 *)(*(int *)(param_1 + 0x48) + 4) = *(undefined4 *)(param_1 + 0x4c);
      }
      if (*(undefined4 **)(param_1 + 0x4c) != (undefined4 *)0x0) {
        **(undefined4 **)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x48);
      }
      *(undefined4 *)(param_1 + 0x48) = 0;
      *(undefined4 *)(param_1 + 0x4c) = 0;
    }
    OS_SPIN_UNLOCK_IRQRESTORE(iVar1,auStack_14);
  }
  return;
}

