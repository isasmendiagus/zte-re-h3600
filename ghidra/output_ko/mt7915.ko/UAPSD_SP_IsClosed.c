// module: mt7915.ko
// function: UAPSD_SP_IsClosed @ 0x1ddb9c
// size: 136 bytes
//

/* WARNING: Removing unreachable block (ram,0x001ddbc0) */
/* WARNING: Removing unreachable block (ram,0x001ddc08) */

bool UAPSD_SP_IsClosed(int param_1,int param_2)

{
  bool bVar1;
  
  _raw_spin_lock_bh("BssTableSortByRssi" + param_1 + 0x10);
  if ((param_2 == 0) || (*(char *)(param_2 + 0xaf8) != '\x01')) {
    bVar1 = true;
  }
  else {
    bVar1 = *(char *)(param_2 + 0xb63) == '\0';
  }
  _raw_spin_unlock_bh();
  return bVar1;
}

