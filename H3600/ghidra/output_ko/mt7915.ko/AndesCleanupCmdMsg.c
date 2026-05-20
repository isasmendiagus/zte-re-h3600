// module: mt7915.ko
// function: AndesCleanupCmdMsg @ 0x1a4a48
// size: 268 bytes
//

void AndesCleanupCmdMsg(int param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  undefined1 auStack_1c [8];
  
  iVar3 = AndesGetSpinLock(param_1 + 0xa7849c);
  if (iVar3 == 0) {
    piVar4 = (int *)*param_2;
    piVar2 = (int *)*piVar4;
    if (piVar4 == param_2) {
      *piVar4 = (int)piVar4;
      piVar4[1] = (int)piVar4;
      return;
    }
  }
  else {
    OS_SPIN_LOCK_IRQSAVE(iVar3,auStack_1c);
    piVar4 = (int *)*param_2;
    piVar2 = (int *)*piVar4;
    if (piVar4 == param_2) {
      *piVar4 = (int)piVar4;
      piVar4[1] = (int)piVar4;
      goto LAB_001a4b10;
    }
  }
  do {
    piVar1 = piVar2;
    if (piVar4 != (int *)0x48) {
      if (*piVar4 != 0) {
        *(int *)(*piVar4 + 4) = piVar4[1];
      }
      if ((int *)piVar4[1] != (int *)0x0) {
        *(int *)piVar4[1] = *piVar4;
      }
      *piVar4 = 0;
      piVar4[1] = 0;
    }
    if ((*(byte *)(piVar4 + -0x11) & 4) == 0) {
      AndesFreeCmdMsg();
    }
    else {
      complete(piVar4 + 2);
    }
    piVar2 = (int *)*piVar1;
    piVar4 = piVar1;
  } while (param_2 != piVar1);
  *param_2 = (int)param_2;
  param_2[1] = (int)param_2;
  if (iVar3 == 0) {
    return;
  }
LAB_001a4b10:
  OS_SPIN_UNLOCK_IRQRESTORE(iVar3,auStack_1c);
  return;
}

