// module: mt7915.ko
// function: MeasureReqLookUp @ 0x13e670
// size: 164 bytes
//

int MeasureReqLookUp(int param_1,uint param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *(int *)(param_1 + 0x795978);
  if (iVar1 != 0) {
    _raw_spin_lock_bh(param_1 + 0x795974);
    for (piVar2 = *(int **)(iVar1 + (param_2 & 0x1f) * 4 + 4);
        (piVar2 != (int *)0x0 && (*(byte *)((int)piVar2 + 9) != param_2)); piVar2 = (int *)*piVar2)
    {
    }
    _raw_spin_unlock_bh(param_1 + 0x795974);
    return (int)piVar2;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s: pMeasureReqTab doesn\'t exist.\n","MeasureReqLookUp");
  return 0;
}

