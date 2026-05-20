// module: mt7915.ko
// function: sae_prepare_commit @ 0x20abd4
// size: 152 bytes
//

int sae_prepare_commit(int param_1)

{
  int iVar1;
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_prepare_commit");
  }
  log_time_begin(0,param_1 + 0x9c);
  if (*(int *)(param_1 + 0x98) != 0) {
    iVar1 = (**(code **)(*(int *)(param_1 + 0x98) + 0x14))(param_1);
    log_time_end(1,"derive_pwe_time",3,param_1 + 0x9c);
    if (iVar1 != 0) {
      return iVar1;
    }
    iVar1 = sae_derive_commit(param_1);
    return iVar1;
  }
  return 1;
}

