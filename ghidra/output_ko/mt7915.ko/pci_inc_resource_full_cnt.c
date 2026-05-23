// module: mt7915.ko
// function: pci_inc_resource_full_cnt @ 0x1d0628
// size: 48 bytes
//

void pci_inc_resource_full_cnt(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(*(int *)(iVar1 + 8) + param_2 * 4);
  *(int *)(iVar1 + 0x20) = *(int *)(iVar1 + 0x20) + 1;
  return;
}

