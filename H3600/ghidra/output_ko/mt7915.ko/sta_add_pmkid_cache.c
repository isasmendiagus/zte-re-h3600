// module: mt7915.ko
// function: sta_add_pmkid_cache @ 0x6b53c
// size: 552 bytes
//

int sta_add_pmkid_cache(int param_1,undefined4 *param_2,void *param_3,void *param_4,byte param_5,
                       byte param_6,int param_7)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *piVar5;
  
  if (*(int *)(param_7 + 0x14) == 0x100) {
    iVar1 = *(int *)(param_7 + 4);
    puVar4 = (undefined4 *)(iVar1 + 0x414c);
    piVar3 = (int *)(iVar1 + 0x42a8);
    piVar5 = (int *)(iVar1 + 0x42ac);
  }
  else {
    iVar1 = (uint)param_6 * 0x2137b0;
    piVar3 = (int *)(&DAT_00580300 + param_1 + iVar1);
    puVar4 = (undefined4 *)(param_1 + iVar1 + 0x5801a1);
    piVar5 = piVar3 + 1;
  }
  iVar1 = sta_search_pmkid_cache(param_1,param_2,(uint)param_6,param_7);
  if (piVar5 != (int *)0x0) {
    _raw_spin_lock_bh(piVar5);
  }
  if (iVar1 == -1) {
    iVar1 = 0;
    puVar2 = puVar4;
    do {
      if (*(char *)((int)puVar2 + 0x56) == '\0') {
        if (0 < DebugLevel) {
          printk("Free Cache entry found,cached_idx %d\n",iVar1);
        }
        *piVar3 = *piVar3 + 1;
        goto LAB_0006b650;
      }
      iVar1 = iVar1 + 1;
      puVar2 = (undefined4 *)((int)puVar2 + 0x57);
    } while (iVar1 != 4);
    if (DebugLevel < 1) {
      iVar1 = 0;
      puVar2 = puVar4;
    }
    else {
      printk("cache full, overwrite cached_idx 0\n");
      iVar1 = 0;
      puVar2 = puVar4;
    }
LAB_0006b650:
    *(undefined1 *)((int)puVar2 + 0x56) = 1;
    *puVar2 = *param_2;
    *(undefined2 *)(puVar2 + 1) = *(undefined2 *)(param_2 + 1);
    memmove((void *)((int)puVar2 + 6),param_3,0x10);
    memmove((void *)((int)puVar2 + 0x16),param_4,(uint)param_5);
    if (2 < DebugLevel) {
      printk("%s(): add %02x:%02x:%02x:%02x:%02x:%02x cache(%d)\n","sta_add_pmkid_cache",
             *(undefined1 *)param_2,*(undefined1 *)((int)param_2 + 1),
             *(undefined1 *)((int)param_2 + 2),*(undefined1 *)((int)param_2 + 3),
             *(undefined1 *)(param_2 + 1),*(undefined1 *)((int)param_2 + 5),iVar1);
    }
  }
  else if (0 < DebugLevel) {
    printk("%s :PMKID found, %d\n","sta_add_pmkid_cache",iVar1);
  }
  if (piVar5 != (int *)0x0) {
    _raw_spin_unlock_bh(piVar5);
  }
  return iVar1;
}

