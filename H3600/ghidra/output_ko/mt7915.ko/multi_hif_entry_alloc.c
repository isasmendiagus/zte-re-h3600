// module: mt7915.ko
// function: multi_hif_entry_alloc @ 0x14e770
// size: 188 bytes
//

undefined4 multi_hif_entry_alloc(undefined4 *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *local_1c [2];
  
  iVar4 = os_alloc_mem(0,local_1c,param_2 + 0x20);
  if (iVar4 == 0) {
    os_zero_mem(local_1c[0],param_2 + 0x20);
    piVar2 = local_1c[0];
    if (local_1c[0] != (int *)0x0) {
      OS_SPIN_LOCK(&DAT_005f3d24);
      piVar1 = DAT_005f3d20;
      iVar4 = _LANCHOR1;
      iVar3 = _LANCHOR1 + 1;
      piVar2[4] = _LANCHOR1;
      _LANCHOR1 = iVar3;
      piVar2[5] = iVar4;
      *piVar2 = *piVar1;
      piVar2[1] = (int)piVar1;
      *(int **)(*piVar1 + 4) = piVar2;
      *piVar1 = (int)piVar2;
      OS_SPIN_UNLOCK(&DAT_005f3d24);
      *param_1 = local_1c[0] + 8;
      return 0;
    }
    os_free_mem(0);
  }
  return 3;
}

