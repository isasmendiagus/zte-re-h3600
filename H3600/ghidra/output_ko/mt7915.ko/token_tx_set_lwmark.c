// module: mt7915.ko
// function: token_tx_set_lwmark @ 0x1d3ffc
// size: 8 bytes
//

void token_tx_set_lwmark(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x28) = param_2;
  return;
}

