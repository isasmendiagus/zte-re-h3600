// module: mt7915.ko
// function: ecc_point_free @ 0x21747c
// size: 68 bytes
//

void ecc_point_free(int *param_1)

{
  if (*param_1 == 0) {
    return;
  }
  Bignum_Free();
  Bignum_Free(*param_1 + 4);
  Bignum_Free(*param_1 + 8);
  os_free_mem(*param_1);
  *param_1 = 0;
  return;
}

