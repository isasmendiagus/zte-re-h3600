// module: mt7915.ko
// function: delete_sae_instance @ 0x208b70
// size: 312 bytes
//

void delete_sae_instance(int param_1)

{
  int iVar1;
  undefined1 uStack_11;
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","delete_sae_instance");
  }
  if (param_1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): pSaeIns is NULL\n","delete_sae_instance");
    }
  }
  else {
    iVar1 = *(int *)(param_1 + 0x180);
    if (iVar1 == 0) {
      if (-1 < DebugLevel) {
        printk("%s(): pSaeCfg is NULL\n","delete_sae_instance");
      }
    }
    else {
      _raw_spin_lock_bh(iVar1 + 0x1b928);
      RTMPReleaseTimer(param_1 + 300,&uStack_11);
      *(undefined1 *)(param_1 + 0x128) = 0;
      *(undefined1 *)(param_1 + 0x129) = 0;
      if (*(int *)(param_1 + 0x98) != 0) {
        (**(code **)(*(int *)(param_1 + 0x98) + 4))(param_1);
      }
      if (*(int *)(param_1 + 0x7c) != 0) {
        os_free_mem();
        *(undefined4 *)(param_1 + 0x7c) = 0;
      }
      Bignum_Free(param_1 + 0x60);
      if (*(int *)(param_1 + 0x17c) != 0) {
        *(undefined4 *)(*(int *)(param_1 + 0x17c) + 0x17c) = 0;
        *(undefined4 *)(param_1 + 0x17c) = 0;
      }
      Bignum_Free(param_1 + 0x50);
      Bignum_Free(param_1 + 0x28);
      __memzero(param_1,0x188);
      *(int *)(iVar1 + 0x1b908) = *(int *)(iVar1 + 0x1b908) + -1;
      _raw_spin_unlock_bh(iVar1 + 0x1b928);
    }
  }
  return;
}

