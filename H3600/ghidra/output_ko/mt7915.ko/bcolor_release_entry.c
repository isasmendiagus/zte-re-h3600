// module: mt7915.ko
// function: bcolor_release_entry @ 0x16b0bc
// size: 76 bytes
//

void bcolor_release_entry(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r1;
  int iVar2;
  
  iVar1 = RcGetBandIdx(*(undefined4 *)(param_2 + 8));
  iVar2 = param_1 + iVar1 * 0x100 + 0x31d4;
  _raw_spin_lock_bh(iVar2);
  param_1 = param_1 + (param_3 + iVar1 * 0x40) * 4;
  *(undefined4 *)(param_1 + 0x30d4) = 0;
  _raw_spin_unlock_bh(iVar2,extraout_r1,param_1 + 0x2d40,param_4);
  return;
}

