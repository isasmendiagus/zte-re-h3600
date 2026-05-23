// module: mt7915.ko
// function: pci_get_resource_state @ 0x1d0688
// size: 44 bytes
//

uint pci_get_resource_state(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  return *(uint *)(*(int *)(*(int *)(iVar1 + 8) + param_2 * 4) + 0x14) & 1;
}

