// module: mt7915.ko
// function: operate_loader_max_amsdu_len @ 0x107970
// size: 24 bytes
//

void operate_loader_max_amsdu_len(int param_1,int param_2)

{
  *(byte *)(param_1 + 0x37) = *(byte *)(param_1 + 0x37) & 0xf7 | (param_2 != 0) << 3;
  return;
}

