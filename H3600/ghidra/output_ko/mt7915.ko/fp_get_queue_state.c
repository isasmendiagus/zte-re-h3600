// module: mt7915.ko
// function: fp_get_queue_state @ 0xd4fac
// size: 12 bytes
//

uint fp_get_queue_state(int param_1)

{
  return *(uint *)(param_1 + 0xc) & 1;
}

