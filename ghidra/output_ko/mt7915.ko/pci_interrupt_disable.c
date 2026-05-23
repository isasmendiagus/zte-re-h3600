// module: mt7915.ko
// function: pci_interrupt_disable @ 0x17a9a4
// size: 160 bytes
//

void pci_interrupt_disable(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(iVar1 + 0xa0);
  hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0xd7014,0);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x74030188,0);
  DataSynchronizationBarrier(0xf);
  if ((*(uint *)(*(int *)(iVar1 + 0xbc) + 0xd7090) & 0x7fffffff) != 0) {
    hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0xd708c,0);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x74020188,0);
  }
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xffffdfff;
  return;
}

