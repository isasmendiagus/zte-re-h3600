// module: mt7915.ko
// function: pci_set_resource_state @ 0x1d06b4
// size: 84 bytes
//

undefined4 pci_set_resource_state(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(*(int *)(iVar1 + 8) + param_2 * 4);
  if (param_3 != 0) {
    _clear_bit(0,iVar1 + 0x14);
    return 0;
  }
  _set_bit(0,iVar1 + 0x14);
  return 0;
}

