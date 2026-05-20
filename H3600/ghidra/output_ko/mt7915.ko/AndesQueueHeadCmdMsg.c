// module: mt7915.ko
// function: AndesQueueHeadCmdMsg @ 0x1a46dc
// size: 112 bytes
//

void AndesQueueHeadCmdMsg(int *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_1c [8];
  
  iVar1 = AndesGetSpinLock(*(int *)(param_2 + 0x1c) + 0xa7849c,param_1);
  if (iVar1 != 0) {
    OS_SPIN_LOCK_IRQSAVE(iVar1,auStack_1c);
    *(undefined4 *)(param_2 + 0x18) = param_3;
    iVar2 = *param_1;
    *(int **)(param_2 + 0x4c) = param_1;
    *(int *)(param_2 + 0x48) = iVar2;
    *(int *)(*param_1 + 4) = param_2 + 0x48;
    *param_1 = param_2 + 0x48;
    OS_SPIN_UNLOCK_IRQRESTORE(iVar1,auStack_1c);
  }
  return;
}

