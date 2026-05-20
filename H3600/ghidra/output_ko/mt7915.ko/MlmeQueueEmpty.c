// module: mt7915.ko
// function: MlmeQueueEmpty @ 0x12d55c
// size: 48 bytes
//

bool MlmeQueueEmpty(int *param_1)

{
  int iVar1;
  
  _raw_spin_lock_bh(param_1 + 3);
  iVar1 = *param_1;
  _raw_spin_unlock_bh(param_1 + 3);
  return iVar1 == 0;
}

