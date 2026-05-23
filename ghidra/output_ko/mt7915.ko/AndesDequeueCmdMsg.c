// module: mt7915.ko
// function: AndesDequeueCmdMsg @ 0x1a4858
// size: 136 bytes
//

int * AndesDequeueCmdMsg(undefined4 param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined1 auStack_14 [8];
  
  iVar1 = AndesGetSpinLock();
  if (iVar1 == 0) {
    piVar3 = (int *)0x0;
  }
  else {
    OS_SPIN_LOCK_IRQSAVE(iVar1,auStack_14);
    piVar2 = (int *)*param_2;
    if (param_2 == piVar2) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = piVar2 + -0x12;
      if (piVar3 != (int *)0x0) {
        if (*piVar2 != 0) {
          *(int *)(*piVar2 + 4) = piVar2[1];
        }
        if ((int *)piVar2[1] != (int *)0x0) {
          *(int *)piVar2[1] = *piVar2;
        }
        *piVar2 = 0;
        piVar2[1] = 0;
      }
    }
    OS_SPIN_UNLOCK_IRQRESTORE(iVar1,auStack_14);
  }
  return piVar3;
}

