// module: mt7915.ko
// function: RTMP_PCI_Writew @ 0x2602f0
// size: 52 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void RTMP_PCI_Writew(undefined2 param_1,undefined2 *param_2)

{
  DataSynchronizationBarrier(0xe);
  if (___aeabi_idivmod != (code *)0x0) {
    (*___aeabi_idivmod)();
  }
  *param_2 = param_1;
  return;
}

