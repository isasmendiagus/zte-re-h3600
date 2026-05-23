// module: mt7915.ko
// function: mt7915_iBFPhaseFreeMem @ 0x8931c
// size: 52 bytes
//

void mt7915_iBFPhaseFreeMem(int param_1)

{
  if (*(int *)(param_1 + 0xa78684) != 0) {
    os_free_mem();
  }
  if (*(int *)(param_1 + 0xa78688) == 0) {
    return;
  }
  os_free_mem();
  return;
}

