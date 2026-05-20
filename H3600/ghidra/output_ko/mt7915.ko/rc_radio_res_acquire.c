// module: mt7915.ko
// function: rc_radio_res_acquire @ 0xaca10
// size: 24 bytes
//

bool rc_radio_res_acquire(int param_1)

{
  return *(char *)(*(int *)(param_1 + 4) + 1) == '\x01';
}

