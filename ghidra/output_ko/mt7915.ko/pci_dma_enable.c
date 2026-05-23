// module: mt7915.ko
// function: pci_dma_enable @ 0x1cc5d4
// size: 56 bytes
//

void pci_dma_enable(void)

{
  undefined4 uVar1;
  
  uVar1 = hc_get_hdev_privdata();
  chip_wait_hif_dma_idle(uVar1,0xff,200,1000);
  RtmpusecDelay(0x32);
  chip_set_hif_dma(uVar1,2,1);
  return;
}

