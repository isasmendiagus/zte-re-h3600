// module: mt7915.ko
// function: RTMP_PCI_Readl @ 0x260354
// size: 16 bytes
//

undefined4 RTMP_PCI_Readl(undefined4 *param_1)

{
  DataSynchronizationBarrier(0xf);
  return *param_1;
}

