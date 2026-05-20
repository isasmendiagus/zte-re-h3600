// module: mt7915.ko
// function: WscInsertPeerEntryByMAC @ 0x1ede00
// size: 216 bytes
//

void WscInsertPeerEntryByMAC(undefined4 *param_1,void *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *local_14;
  
  local_14 = (undefined4 *)0x0;
  local_14 = (undefined4 *)WscFindPeerEntry();
  if (local_14 == (undefined4 *)0x0) {
    os_alloc_mem(0,&local_14,0x10);
    if (local_14 != (undefined4 *)0x0) {
      __memzero(local_14,0x10);
      puVar2 = local_14;
      *local_14 = 0;
      memmove(local_14 + 2,param_2,6);
      uVar1 = jiffies;
      *puVar2 = 0;
      puVar2[1] = uVar1;
      if ((undefined4 *)param_1[1] == (undefined4 *)0x0) {
        *param_1 = puVar2;
      }
      else {
        *(undefined4 *)param_1[1] = puVar2;
      }
      param_1[1] = puVar2;
      *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
      if (local_14 != (undefined4 *)0x0) {
        return;
      }
    }
    printk(&_LC279,0x345e);
    dump_stack();
  }
  else {
    local_14[1] = jiffies;
  }
  return;
}

