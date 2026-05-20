// module: mt7915.ko
// function: pci_mcu_fw_init @ 0x1caee0
// size: 112 bytes
//

void pci_mcu_fw_init(void)

{
  int iVar1;
  
  iVar1 = hc_get_hdev_privdata();
  if (2 < DebugLevel) {
    printk(&_LC5,"pci_mcu_fw_init");
  }
  *(undefined4 *)(iVar1 + 0xa7861c) = 0;
  chip_interrupt_enable(iVar1);
  hif_dma_enable(*(undefined4 *)(iVar1 + 0xa797a0));
  *(uint *)(iVar1 + 0xa39f84) = *(uint *)(iVar1 + 0xa39f84) | 0x11000000;
  return;
}

