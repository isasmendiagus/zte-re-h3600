// module: mt7915.ko
// function: RTMP_PCI_Readb @ 0x260374
// size: 16 bytes
//

undefined1 RTMP_PCI_Readb(undefined1 *param_1)

{
  DataSynchronizationBarrier(0xf);
  return *param_1;
}

