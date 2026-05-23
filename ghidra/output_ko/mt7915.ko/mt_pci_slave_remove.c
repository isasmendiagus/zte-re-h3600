// module: mt7915.ko
// function: mt_pci_slave_remove @ 0x1d90b8
// size: 48 bytes
//

void mt_pci_slave_remove(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xc0);
  __arm_iounmap(*(undefined4 *)(iVar1 + 0xbc));
  pci_release_regions(param_1);
  pci_disable_device(param_1);
  pci_hif_chip_exit(iVar1,extraout_r1,extraout_r2,param_4);
  return;
}

