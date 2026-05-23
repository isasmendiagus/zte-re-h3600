// module: mt7915.ko
// function: mt7915_iBFPhaseCalInit @ 0x89350
// size: 140 bytes
//

void mt7915_iBFPhaseCalInit(int param_1)

{
  mt7915_iBFPhaseFreeMem();
  os_alloc_mem(param_1,param_1 + 0xa78684,0x28);
  os_alloc_mem(param_1,param_1 + 0xa78688,0x140);
  if (*(int *)(param_1 + 0xa78684) != 0) {
    __memzero(*(int *)(param_1 + 0xa78684),0x28);
  }
  if (*(int *)(param_1 + 0xa78688) != 0) {
    __memzero(*(int *)(param_1 + 0xa78688),0x140);
  }
  *(undefined1 *)(param_1 + 0xa7868c) = 0;
  __memzero(param_1 + 0xa7868d,9);
  return;
}

