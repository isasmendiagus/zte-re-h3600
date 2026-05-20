// module: mt7915.ko
// function: a4_add_entry @ 0x9f224
// size: 224 bytes
//

void a4_add_entry(int param_1,int param_2,undefined2 param_3)

{
  int iVar1;
  int *piVar2;
  int *local_14;
  
  local_14 = (int *)0x0;
  iVar1 = a4_lookup_entry_by_wcid();
  if (iVar1 == 0) {
    os_alloc_mem(param_1,&local_14,0xc);
    if (local_14 != (int *)0x0) {
      __memzero(local_14,0xc);
      *(undefined2 *)((int)local_14 + 10) = param_3;
      *(undefined1 *)(local_14 + 2) = 1;
      _raw_spin_lock_bh("Query::OID_802_11_STATISTICS\n" + param_1 + param_2 * 0x5834 + 0x1c);
      piVar2 = *(int **)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" +
                        param_1 + param_2 * 0x5834 + 4);
      *local_14 = *piVar2;
      local_14[1] = (int)piVar2;
      *(int **)(*piVar2 + 4) = local_14;
      *piVar2 = (int)local_14;
      _raw_spin_unlock_bh("Query::OID_802_11_STATISTICS\n" + param_1 + param_2 * 0x5834 + 0x1c);
      return;
    }
    if (-1 < DebugLevel) {
      printk("%s: Fail to alloc memory for pNewConnEntry\n","a4_add_entry");
    }
  }
  return;
}

