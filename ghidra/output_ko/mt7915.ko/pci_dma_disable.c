// module: mt7915.ko
// function: pci_dma_disable @ 0x1cc5bc
// size: 24 bytes
//

void pci_dma_disable(void)

{
  undefined4 uVar1;
  undefined4 in_r3;
  
  uVar1 = hc_get_hdev_privdata();
  chip_set_hif_dma(uVar1,2,0,in_r3);
  return;
}

