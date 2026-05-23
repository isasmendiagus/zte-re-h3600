// module: mt7915.ko
// function: token_tx_get_state @ 0x1d3fa0
// size: 12 bytes
//

uint token_tx_get_state(int param_1)

{
  return *(uint *)(param_1 + 0x30) & 1;
}

