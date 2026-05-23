// module: mt7915.ko
// function: pci_is_tx_resource_empty @ 0x1d0598
// size: 56 bytes
//

bool pci_is_tx_resource_empty(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(*(int *)(iVar1 + 8) + param_2 * 4);
  return *(int *)(iVar1 + 8) == *(int *)(iVar1 + 0x28);
}

