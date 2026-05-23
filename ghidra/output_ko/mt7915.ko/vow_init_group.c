// module: mt7915.ko
// function: vow_init_group @ 0x4264c
// size: 136 bytes
//

void vow_init_group(int param_1)

{
  if ((*(uint *)(param_1 + 0xa7a2e8) & 0xff00ff) == 0) {
    return;
  }
  if ((*(uint *)(param_1 + 0xa797a8) & 2) == 0) {
    return;
  }
  vow_set_group(param_1,0,0x30);
  vow_set_group(param_1,0,0x10);
  if ((*(uint *)(param_1 + 0xa797a8) & 2) != 0) {
    FUN_000403f8(param_1);
  }
  *(bool *)(param_1 + 0xa7a2fc) = *(char *)(param_1 + 0xa7a2e8) != '\0';
  vow_set_at_estimator(param_1,1);
  return;
}

