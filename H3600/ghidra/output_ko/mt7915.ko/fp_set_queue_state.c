// module: mt7915.ko
// function: fp_set_queue_state @ 0xd4fb8
// size: 56 bytes
//

undefined4 fp_set_queue_state(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_2 != 0) {
    _clear_bit(0,param_1 + 0xc);
    return 0;
  }
  _set_bit(0,param_1 + 0xc,param_3,param_1,param_4);
  return 0;
}

