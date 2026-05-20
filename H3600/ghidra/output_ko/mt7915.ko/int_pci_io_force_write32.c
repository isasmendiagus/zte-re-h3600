// module: mt7915.ko
// function: int_pci_io_force_write32 @ 0x1ca728
// size: 64 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void int_pci_io_force_write32(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_hif_ctrl();
  DataSynchronizationBarrier(0xe);
  if (___aeabi_idivmod != (code *)0x0) {
    (*___aeabi_idivmod)();
  }
  *(undefined4 *)(*(int *)(iVar1 + 0x84) + param_2) = param_3;
  return;
}

