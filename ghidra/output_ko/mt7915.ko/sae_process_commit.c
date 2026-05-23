// module: mt7915.ko
// function: sae_process_commit @ 0x209f34
// size: 296 bytes
//

bool sae_process_commit(int param_1)

{
  int iVar1;
  bool bVar2;
  int local_1c;
  
  local_1c = 0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_process_commit");
  }
  log_time_begin(0,param_1 + 0x100);
  os_alloc_mem(0,&local_1c,0x400);
  if (local_1c != 0) {
    if ((*(int *)(param_1 + 0x98) == 0) ||
       (iVar1 = (**(code **)(*(int *)(param_1 + 0x98) + 0x18))(param_1), iVar1 != 1)) {
      bVar2 = true;
    }
    else {
      log_time_end(1,"derive_k_time",3,param_1 + 0x100);
      log_time_begin(0,param_1 + 0x114);
      iVar1 = sae_derive_key(param_1,local_1c);
      bVar2 = iVar1 != 1;
      log_time_end(1,"derive_pmk_time",3,param_1 + 0x114);
    }
    if (2 < DebugLevel) {
      printk("%s() <==, res = %d\n","sae_process_commit",bVar2);
    }
    os_free_mem(local_1c);
    return bVar2;
  }
  return true;
}

