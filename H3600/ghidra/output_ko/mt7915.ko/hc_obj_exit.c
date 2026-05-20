// module: mt7915.ko
// function: hc_obj_exit @ 0xaa6c4
// size: 20 bytes
//

void hc_obj_exit(int param_1)

{
  *(undefined4 *)(*(int *)(param_1 + 0xabc) + 0x24) = 0;
  *(undefined4 *)(param_1 + 0xabc) = 0;
  return;
}

