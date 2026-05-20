// module: mt7915.ko
// function: multi_hif_acquire_id @ 0x14e70c
// size: 100 bytes
//

undefined4 multi_hif_acquire_id(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  if (param_1 != (int *)0x0) {
    OS_SPIN_LOCK(&DAT_005f3d24);
    piVar2 = DAT_005f3d20;
    iVar1 = _LANCHOR1;
    iVar3 = _LANCHOR1 + 1;
    param_1[4] = _LANCHOR1;
    _LANCHOR1 = iVar3;
    param_1[5] = iVar1;
    *param_1 = *piVar2;
    param_1[1] = (int)piVar2;
    *(int **)(*piVar2 + 4) = param_1;
    *piVar2 = (int)param_1;
    OS_SPIN_UNLOCK(&DAT_005f3d24);
    return 0;
  }
  return 2;
}

