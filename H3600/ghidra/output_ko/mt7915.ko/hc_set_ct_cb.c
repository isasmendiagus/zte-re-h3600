// module: mt7915.ko
// function: hc_set_ct_cb @ 0xaac10
// size: 8 bytes
//

void hc_set_ct_cb(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0xa8c) = param_2;
  return;
}

