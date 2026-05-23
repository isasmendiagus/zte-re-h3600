// module: mt7915.ko
// function: AndesQueueLen @ 0x1a474c
// size: 92 bytes
//

int AndesQueueLen(undefined4 param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined1 auStack_14 [4];
  
  iVar1 = AndesGetSpinLock();
  if (iVar1 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = 0;
    OS_SPIN_LOCK_IRQSAVE(iVar1,auStack_14);
    for (piVar2 = (int *)*param_2; param_2 != piVar2; piVar2 = (int *)*piVar2) {
      iVar3 = iVar3 + 1;
    }
    OS_SPIN_UNLOCK_IRQRESTORE(iVar1,auStack_14);
  }
  return iVar3;
}

