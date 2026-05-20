// module: mt7915.ko
// function: wdev_search_by_band_omac_idx @ 0x14e038
// size: 160 bytes
//

int wdev_search_by_band_omac_idx(int param_1,uint param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = (int *)(param_1 + 8);
  _raw_spin_lock_bh(piVar3);
  piVar1 = piVar3;
  while( true ) {
    piVar1 = piVar1 + 1;
    iVar2 = *piVar1;
    if (((iVar2 != 0) && (*(byte *)(iVar2 + 0xaa7) == param_2)) &&
       (*(byte *)(iVar2 + 0x29) == param_3)) break;
    if (piVar1 == (int *)(param_1 + 0x1a8)) {
      _raw_spin_unlock_bh(piVar3);
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s: can not find registered wdev\n","wdev_search_by_band_omac_idx");
      return 0;
    }
  }
  _raw_spin_unlock_bh(piVar3);
  return iVar2;
}

