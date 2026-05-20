// module: mt7915.ko
// function: pci_get_resource_idx @ 0x1ca768
// size: 40 bytes
//

undefined1 pci_get_resource_idx(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  iVar1 = hc_get_hif_ctrl();
  return *(undefined1 *)(iVar1 + (param_3 + param_2 * 8) * 4 + param_4 + 0x24);
}

