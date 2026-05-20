// module: mt7915.ko
// function: operate_loader_min_mpdu_start_space @ 0x107988
// size: 16 bytes
//

void operate_loader_min_mpdu_start_space(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x38) = *(byte *)(param_1 + 0x38) & 0xe3 | (param_2 & 7) << 2;
  return;
}

