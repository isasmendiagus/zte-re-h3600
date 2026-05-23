// module: mt7915.ko
// function: pci_get_resouce_type @ 0x1ca55c
// size: 16 bytes
//

undefined4 pci_get_resouce_type(int param_1,int param_2)

{
  return **(undefined4 **)(*(int *)(param_1 + 4) + param_2 * 4);
}

