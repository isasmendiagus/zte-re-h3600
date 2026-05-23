// module: mt7915.ko
// function: search_sae_instance @ 0x2089fc
// size: 368 bytes
//

int search_sae_instance(int param_1,void *param_2,void *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  void *__s1;
  int iVar4;
  int iVar5;
  
  iVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(*(int *)(param_1 + 0x1b924) + 0xa797a0));
  if (4 < DebugLevel) {
    printk("==> %s()\n","search_sae_instance");
  }
  if (param_1 == 0 || (param_3 == (void *)0x0 || param_2 == (void *)0x0)) {
    if (-1 < DebugLevel) {
      printk("%s(): search fail with null input\n","search_sae_instance");
      return 0;
    }
  }
  else {
    iVar3 = param_1 + 0x1b928;
    _raw_spin_lock_bh(iVar3);
    if (iVar1 != 0) {
      __s1 = (void *)(param_1 + 0x166);
      iVar4 = 0;
      iVar5 = 0;
      do {
        if (*(char *)((int)__s1 + -0x3e) != '\0') {
          iVar2 = memcmp((void *)((int)__s1 + -6),param_2,6);
          iVar5 = iVar5 + 1;
          if ((iVar2 == 0) && (iVar2 = memcmp(__s1,param_3,6), iVar2 == 0)) {
            _raw_spin_unlock_bh(iVar3);
            iVar1 = param_1 + iVar4 * 0x188;
            if (*(int *)(param_1 + iVar4 * 0x188) != 3) {
              return iVar1;
            }
            if (*(int *)(iVar1 + 0x17c) == 0) {
              return iVar1;
            }
            return *(int *)(iVar1 + 0x17c);
          }
          if (*(int *)(param_1 + 0x1b908) == iVar5) break;
        }
        iVar4 = iVar4 + 1;
        __s1 = (void *)((int)__s1 + 0x188);
      } while (iVar4 != iVar1);
    }
    _raw_spin_unlock_bh(iVar3);
  }
  return 0;
}

