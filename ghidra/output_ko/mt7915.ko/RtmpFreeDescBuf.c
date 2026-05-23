// module: mt7915.ko
// function: RtmpFreeDescBuf @ 0x25fecc
// size: 64 bytes
//

void RtmpFreeDescBuf(int param_1)

{
  undefined4 *puVar1;
  
  if ((param_1 == 0) || (puVar1 = *(undefined4 **)(param_1 + 0x10c), puVar1 == (undefined4 *)0x0)) {
    puVar1 = &arm_dma_ops;
  }
  (*(code *)puVar1[1])();
  return;
}

