// module: mt7915.ko
// function: MeasureReqTabExit @ 0x13e648
// size: 40 bytes
//

void MeasureReqTabExit(int param_1)

{
  if (*(int *)(param_1 + 0x795978) == 0) {
    return;
  }
  os_free_mem();
  *(undefined4 *)(param_1 + 0x795978) = 0;
  return;
}

