// module: mt7915.ko
// function: pci_rx_event_process @ 0x1ca584
// size: 44 bytes
//

void pci_rx_event_process(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0x18) == 10) {
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("unknown msg state(%d)\n");
  return;
}

