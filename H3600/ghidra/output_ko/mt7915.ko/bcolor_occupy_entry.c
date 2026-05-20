// module: mt7915.ko
// function: bcolor_occupy_entry @ 0x16b108
// size: 84 bytes
//

void bcolor_occupy_entry(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = RcGetBandIdx(*(undefined4 *)(param_2 + 8));
  uVar1 = jiffies;
  iVar3 = param_1 + iVar2 * 0x100 + 0x31d4;
  _raw_spin_lock_bh(iVar3);
  *(undefined4 *)(param_1 + (param_3 + iVar2 * 0x40) * 4 + 0x30d4) = uVar1;
  _raw_spin_unlock_bh(iVar3);
  return;
}

