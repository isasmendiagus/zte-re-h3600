// module: mt7915.ko
// function: token_tx_inc_full_cnt @ 0x1d3fe4
// size: 16 bytes
//

void token_tx_inc_full_cnt(int param_1)

{
  *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 1;
  return;
}

