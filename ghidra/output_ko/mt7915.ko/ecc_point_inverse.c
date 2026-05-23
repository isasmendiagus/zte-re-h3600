// module: mt7915.ko
// function: ecc_point_inverse @ 0x218620
// size: 152 bytes
//

void ecc_point_inverse(int param_1,undefined4 param_2,undefined4 param_3)

{
  int local_14;
  
  local_14 = 0;
  if (2 < DebugLevel) {
    printk("==> %s()\n","ecc_point_inverse");
  }
  if (param_1 != 0) {
    ecc_point_copy(param_1,&local_14);
    Bignum_Sub(param_2,*(undefined4 *)(param_1 + 4),local_14 + 4);
    ecc_point_copy(local_14,param_3);
    ecc_point_free(&local_14);
    return;
  }
  ecc_point_free(param_3);
  return;
}

