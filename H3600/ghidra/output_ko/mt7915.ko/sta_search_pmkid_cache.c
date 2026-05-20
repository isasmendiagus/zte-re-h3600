// module: mt7915.ko
// function: sta_search_pmkid_cache @ 0x6b3e8
// size: 336 bytes
//

int sta_search_pmkid_cache(int param_1,undefined1 *param_2,int param_3,int param_4)

{
  int iVar1;
  void *__s1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(param_4 + 0x14) == 0x100) {
    __s1 = (void *)(*(int *)(param_4 + 4) + 0x414c);
    iVar3 = *(int *)(param_4 + 4) + 0x42ac;
  }
  else {
    param_1 = param_1 + param_3 * 0x2137b0 + 0x580000;
    iVar3 = param_1 + 0x304;
    __s1 = (void *)(param_1 + 0x1a1);
  }
  if (iVar3 != 0) {
    _raw_spin_lock_bh(iVar3);
  }
  iVar2 = 0;
  while ((*(char *)((int)__s1 + 0x56) != '\x01' || (iVar1 = memcmp(__s1,param_2,6), iVar1 != 0))) {
    iVar2 = iVar2 + 1;
    __s1 = (void *)((int)__s1 + 0x57);
    if (iVar2 == 4) {
      if (iVar3 != 0) {
        _raw_spin_unlock_bh(iVar3);
      }
      if (2 < DebugLevel) {
        printk("%s():  not found\n","sta_search_pmkid_cache");
      }
      return -1;
    }
  }
  if (2 < DebugLevel) {
    printk("%s():%02x:%02x:%02x:%02x:%02x:%02x cache(%d)\n","sta_search_pmkid_cache",*param_2,
           param_2[1],param_2[2],param_2[3],param_2[4],param_2[5],iVar2);
  }
  if (iVar3 != 0) {
    _raw_spin_unlock_bh(iVar3);
    return iVar2;
  }
  return iVar2;
}

