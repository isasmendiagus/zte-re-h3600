// module: mt7915.ko
// function: MlmeDequeue @ 0x12cfe0
// size: 116 bytes
//

undefined4 MlmeDequeue(int *param_1,undefined4 *param_2)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = param_1 + 3;
  _raw_spin_lock_bh(piVar2);
  if (*param_1 != 0) {
    *param_2 = param_1 + param_1[1] * 0x24c + 4;
    iVar1 = param_1[1] + 1;
    *param_1 = *param_1 + -1;
    if (iVar1 == 0x100) {
      iVar1 = 0;
    }
    param_1[1] = iVar1;
    _raw_spin_unlock_bh(piVar2);
    return 1;
  }
  _raw_spin_unlock_bh(piVar2);
  return 0;
}

