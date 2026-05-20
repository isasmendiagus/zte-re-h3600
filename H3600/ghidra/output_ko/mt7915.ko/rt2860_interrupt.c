// module: mt7915.ko
// function: rt2860_interrupt @ 0x25fe3c
// size: 40 bytes
//

void rt2860_interrupt(undefined4 param_1,undefined4 param_2)

{
  pci_handle_irq(param_2);
  g_stWlanFactoryStatistics._0_4_ = g_stWlanFactoryStatistics._0_4_ + 1;
  return;
}

