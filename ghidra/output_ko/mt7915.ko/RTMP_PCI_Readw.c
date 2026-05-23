// module: mt7915.ko
// function: RTMP_PCI_Readw @ 0x260364
// size: 16 bytes
//

undefined2 RTMP_PCI_Readw(undefined2 *param_1)

{
  DataSynchronizationBarrier(0xf);
  return *param_1;
}

