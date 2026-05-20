// module: mt7915.ko
// function: ge_get_psq_pkt @ 0xcfe94
// size: 100 bytes
//

int * ge_get_psq_pkt(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = param_2 + 0xa4;
  _raw_spin_lock_bh(iVar3);
  piVar2 = *(int **)(param_2 + 100);
  if (piVar2 != (int *)0x0) {
    iVar1 = *piVar2;
    *piVar2 = 0;
    *(int *)(param_2 + 100) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)(param_2 + 0x68) = 0;
    }
    *(int *)(param_2 + 0x6c) = *(int *)(param_2 + 0x6c) + -1;
    _raw_spin_unlock_bh(iVar3);
    return piVar2;
  }
  _raw_spin_unlock_bh(iVar3);
  return (int *)0x0;
}

