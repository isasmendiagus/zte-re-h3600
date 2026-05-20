// module: mt7915.ko
// function: token_tx_set_state @ 0x1d3fac
// size: 56 bytes
//

undefined4 token_tx_set_state(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_2 != 0) {
    _clear_bit(0,param_1 + 0x30);
    return 0;
  }
  _set_bit(0,param_1 + 0x30,param_3,param_1,param_4);
  return 0;
}

