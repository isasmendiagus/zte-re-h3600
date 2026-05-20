// module: mt7915.ko
// function: AndesQueueTailCmdMsg @ 0x1a4668
// size: 116 bytes
//

void AndesQueueTailCmdMsg(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined1 auStack_1c [8];
  
  iVar1 = AndesGetSpinLock(*(int *)(param_2 + 0x1c) + 0xa7849c,param_1);
  if (iVar1 != 0) {
    OS_SPIN_LOCK_IRQSAVE(iVar1,auStack_1c);
    *(undefined4 *)(param_2 + 0x18) = param_3;
    piVar2 = *(int **)(param_1 + 4);
    iVar3 = *piVar2;
    *(int **)(param_2 + 0x4c) = piVar2;
    *(int *)(param_2 + 0x48) = iVar3;
    *(int *)(*piVar2 + 4) = param_2 + 0x48;
    *piVar2 = param_2 + 0x48;
    OS_SPIN_UNLOCK_IRQRESTORE(iVar1,auStack_1c);
  }
  return;
}

