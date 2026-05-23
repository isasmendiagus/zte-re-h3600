// module: mt7915.ko
// function: hc_get_chip_tx_token_nums @ 0xa8984
// size: 8 bytes
//

undefined4 hc_get_chip_tx_token_nums(int param_1)

{
  return *(undefined4 *)(param_1 + 0xb40);
}

