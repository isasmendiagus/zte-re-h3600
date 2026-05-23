// module: mt7915.ko
// function: hif_core_ops_register @ 0x1df690
// size: 20 bytes
//

void hif_core_ops_register(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_2;
  if (param_2 != 1) {
    iVar1 = param_2 + -4;
  }
  if (iVar1 != 0 && (param_2 != 1 && param_2 + -4 != 1)) {
    return;
  }
  pci_core_ops_register();
  return;
}

