// module: mt7915.ko
// function: operate_loader_support_ch_width_set @ 0x1079a8
// size: 16 bytes
//

void operate_loader_support_ch_width_set(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x36) = *(byte *)(param_1 + 0x36) & 0xfd | (param_2 & 1) << 1;
  return;
}

