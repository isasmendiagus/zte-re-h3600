// module: mt7915.ko
// function: hc_get_chip_sw_tx_token_nums @ 0xa898c
// size: 16 bytes
//

int hc_get_chip_sw_tx_token_nums(int param_1)

{
  return *(int *)(param_1 + 0xb40) - *(int *)(param_1 + 0xb4c);
}

