// module: mt7915.ko
// function: operate_loader_smps @ 0x1079b8
// size: 16 bytes
//

void operate_loader_smps(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x36) = *(byte *)(param_1 + 0x36) & 0xf3 | (param_2 & 3) << 2;
  return;
}

