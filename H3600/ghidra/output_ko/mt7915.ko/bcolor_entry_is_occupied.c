// module: mt7915.ko
// function: bcolor_entry_is_occupied @ 0x16b15c
// size: 84 bytes
//

bool bcolor_entry_is_occupied(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = RcGetBandIdx(*(undefined4 *)(param_2 + 8));
  iVar2 = param_1 + iVar1 * 0x100 + 0x31d4;
  _raw_spin_lock_bh(iVar2);
  iVar1 = *(int *)(param_1 + (param_3 + iVar1 * 0x40) * 4 + 0x30d4);
  _raw_spin_unlock_bh(iVar2);
  return iVar1 != 0;
}

