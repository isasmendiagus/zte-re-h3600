// module: mt7915.ko
// function: vow_reset @ 0x48e74
// size: 44 bytes
//

void vow_reset(int param_1)

{
  if (*(char *)(param_1 + 0xa7a32c) != '\0') {
    FUN_000405bc();
  }
  vow_reset_dvt(param_1);
  return;
}

