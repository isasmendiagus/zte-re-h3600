// module: mt7915.ko
// function: vow_reset_watf @ 0x48b3c
// size: 24 bytes
//

void vow_reset_watf(int param_1)

{
  if (*(char *)(param_1 + 0xa7a32c) == '\0') {
    return;
  }
  FUN_000405bc();
  return;
}

