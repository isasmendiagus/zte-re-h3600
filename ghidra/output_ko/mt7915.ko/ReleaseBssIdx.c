// module: mt7915.ko
// function: ReleaseBssIdx @ 0x14d5ec
// size: 112 bytes
//

void ReleaseBssIdx(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = param_1 + 0x286290;
  _raw_spin_lock_bh(iVar1);
  if (0x1f < param_2) {
    *(uint *)(param_1 + 0x28628c) = *(uint *)(param_1 + 0x28628c) & ~(1 << (param_2 - 0x20 & 0xff));
    _raw_spin_unlock_bh(iVar1);
    return;
  }
  *(uint *)(param_1 + 0x286288) = *(uint *)(param_1 + 0x286288) & ~(1 << (param_2 & 0xff));
  _raw_spin_unlock_bh(iVar1);
  return;
}

