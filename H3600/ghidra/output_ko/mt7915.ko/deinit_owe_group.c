// module: mt7915.ko
// function: deinit_owe_group @ 0x21c838
// size: 172 bytes
//

undefined4 deinit_owe_group(undefined4 *param_1)

{
  if (param_1[2] != 0) {
    ecc_point_free(param_1 + 2);
    param_1[2] = 0;
  }
  if (param_1[3] != 0) {
    ecc_point_free(param_1 + 3);
    param_1[3] = 0;
  }
  if (param_1[4] != 0) {
    ecc_point_free(param_1 + 4);
    param_1[4] = 0;
  }
  if (param_1[5] != 0) {
    Bignum_Free(param_1 + 5);
    param_1[5] = 0;
  }
  if (param_1[7] != 0) {
    os_free_mem();
    param_1[7] = 0;
  }
  *param_1 = 0;
  param_1[1] = 0;
  *(undefined1 *)(param_1 + 6) = 0;
  *(undefined1 *)((int)param_1 + 0x19) = 0;
  return 0;
}

