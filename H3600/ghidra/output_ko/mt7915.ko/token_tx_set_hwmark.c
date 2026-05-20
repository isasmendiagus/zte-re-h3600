// module: mt7915.ko
// function: token_tx_set_hwmark @ 0x1d400c
// size: 8 bytes
//

void token_tx_set_hwmark(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x2c) = param_2;
  return;
}

