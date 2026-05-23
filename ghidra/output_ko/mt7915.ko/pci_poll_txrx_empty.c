// module: mt7915.ko
// function: pci_poll_txrx_empty @ 0x1cc56c
// size: 80 bytes
//

void pci_poll_txrx_empty(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_hdev_privdata();
  RtmpOsMsDelay(100);
  *(uint *)(iVar1 + 0xa39f84) = *(uint *)(iVar1 + 0xa39f84) | 0x80000000;
  chip_wait_hif_dma_idle(iVar1,param_2,20000,0x32);
  *(uint *)(iVar1 + 0xa39f84) = *(uint *)(iVar1 + 0xa39f84) & 0x7fffffff;
  return;
}

