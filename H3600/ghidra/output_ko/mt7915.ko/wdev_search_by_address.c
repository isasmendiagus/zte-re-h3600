// module: mt7915.ko
// function: wdev_search_by_address @ 0x14ded4
// size: 204 bytes
//

int wdev_search_by_address(int param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  piVar4 = (int *)(param_1 + 8);
  _raw_spin_lock_bh(piVar4);
  piVar3 = piVar4;
  do {
    piVar3 = piVar3 + 1;
    iVar2 = *piVar3;
    if ((iVar2 != 0) && (iVar1 = memcmp(param_2,(void *)(iVar2 + 0x1b),6), iVar1 == 0)) {
      _raw_spin_unlock_bh(piVar4);
      return iVar2;
    }
  } while (piVar3 != (int *)(param_1 + 0x1a8));
  _raw_spin_unlock_bh(piVar4);
  if (((&DAT_0036790d)[param_1] != '\0') && (iVar2 = lookup_rept_entry(param_1,param_2), iVar2 != 0)
     ) {
    return iVar2 + 0xe0;
  }
  if (DebugLevel < 4) {
    return 0;
  }
  printk("%s: can not find registered wdev\n","wdev_search_by_address");
  return 0;
}

