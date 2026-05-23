// module: mt7915.ko
// function: pci_dma_reset @ 0x1cec94
// size: 104 bytes
//

void pci_dma_reset(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = hc_get_hdev_privdata();
  chip_set_hif_dma(uVar1,2,0);
  iVar2 = chip_wait_hif_dma_idle(uVar1,0xff,200,1000);
  if (iVar2 != 0) {
    chip_reset_hif_dma(uVar1);
    return;
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("<== %s(): WPDMA reset fail! \n","pci_dma_reset");
  return;
}

