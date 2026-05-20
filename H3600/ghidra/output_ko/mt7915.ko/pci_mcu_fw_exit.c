// module: mt7915.ko
// function: pci_mcu_fw_exit @ 0x1cae78
// size: 100 bytes
//

void pci_mcu_fw_exit(void)

{
  int iVar1;
  
  iVar1 = hc_get_hdev_privdata();
  if (2 < DebugLevel) {
    printk(&_LC5,"pci_mcu_fw_exit");
  }
  *(uint *)(iVar1 + 0xa39f84) = *(uint *)(iVar1 + 0xa39f84) & 0xeeffffff;
  hif_dma_disable(*(undefined4 *)(iVar1 + 0xa797a0));
  chip_interrupt_disable(iVar1);
  return;
}

