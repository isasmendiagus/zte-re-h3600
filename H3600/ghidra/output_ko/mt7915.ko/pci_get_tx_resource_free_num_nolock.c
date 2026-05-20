// module: mt7915.ko
// function: pci_get_tx_resource_free_num_nolock @ 0x1d0558
// size: 64 bytes
//

int pci_get_tx_resource_free_num_nolock(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(*(int *)(iVar1 + 8) + param_2 * 4);
  iVar2 = *(uint *)(iVar1 + 0x10) - 1;
  if (*(uint *)(iVar1 + 0x10) <= *(uint *)(iVar1 + 0x28)) {
    iVar2 = iVar2 + (uint)*(ushort *)(iVar1 + 0x5a);
  }
  return iVar2 - *(uint *)(iVar1 + 0x28);
}

