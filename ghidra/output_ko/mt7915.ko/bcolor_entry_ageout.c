// module: mt7915.ko
// function: bcolor_entry_ageout @ 0x16b1b0
// size: 128 bytes
//

void bcolor_entry_ageout(int param_1,int param_2,short param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar2 = RcGetBandIdx(*(undefined4 *)(param_2 + 8));
  iVar1 = jiffies;
  iVar2 = iVar2 * 0x100;
  iVar4 = param_1 + iVar2 + 0x31d4;
  _raw_spin_lock_bh(iVar4);
  piVar3 = (int *)(param_1 + iVar2 + 0x30d4);
  do {
    piVar3 = piVar3 + 1;
    if ((param_3 * 100 + *piVar3) - iVar1 < 0) {
      *piVar3 = 0;
    }
  } while (piVar3 != (int *)(param_1 + iVar2 + 0x31d0));
  _raw_spin_unlock_bh(iVar4);
  return;
}

