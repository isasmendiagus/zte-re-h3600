// module: mt7915.ko
// function: ge_set_swq_state @ 0xd219c
// size: 36 bytes
//

undefined4 ge_set_swq_state(int param_1,int param_2,undefined1 param_3)

{
  *(undefined1 *)(param_1 + param_2 * 0x4018 + 0x28a35c) = param_3;
  return 0;
}

