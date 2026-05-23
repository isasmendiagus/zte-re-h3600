// module: mt7915.ko
// function: operate_loader_ht_max_ampdu_len_exp @ 0x107998
// size: 16 bytes
//

void operate_loader_ht_max_ampdu_len_exp(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x38) = *(byte *)(param_1 + 0x38) & 0xfc | param_2 & 3;
  return;
}

