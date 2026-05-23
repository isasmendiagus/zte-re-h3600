// module: mt7915.ko
// function: MeasureReqDelete @ 0x13e978
// size: 280 bytes
//

void MeasureReqDelete(int param_1)

{
  int *piVar1;
  int *piVar2;
  char *pcVar3;
  int *piVar4;
  uint uVar5;
  
  pcVar3 = *(char **)(param_1 + 0x795978);
  if (pcVar3 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: pMeasureReqTab doesn\'t exist.\n","MeasureReqDelete");
      return;
    }
    return;
  }
  if (*pcVar3 == '\0') {
    if (-1 < DebugLevel) {
      printk("pMeasureReqTab empty.\n");
      return;
    }
    return;
  }
  piVar2 = (int *)MeasureReqLookUp();
  if (piVar2 == (int *)0x0) {
    return;
  }
  uVar5 = *(byte *)((int)piVar2 + 9) & 0x1f;
  piVar4 = *(int **)(pcVar3 + uVar5 * 4 + 4);
  _raw_spin_lock_bh(param_1 + 0x795974);
  if (piVar2 == piVar4) {
LAB_0013ea84:
    *(int *)(pcVar3 + uVar5 * 4 + 4) = *piVar2;
  }
  else {
    for (piVar1 = (int *)*piVar4; piVar1 != (int *)0x0; piVar1 = (int *)*piVar1) {
      if (piVar2 == piVar1) {
        if (piVar4 == (int *)0x0) goto LAB_0013ea84;
        *piVar4 = *piVar2;
        break;
      }
      piVar4 = piVar1;
    }
  }
  __memzero(piVar2,0x84);
  *pcVar3 = *pcVar3 + -1;
  _raw_spin_unlock_bh(param_1 + 0x795974);
  return;
}

