// module: mt7915.ko
// function: Bignum_Free @ 0x20c2a8
// size: 36 bytes
//

void Bignum_Free(undefined4 *param_1)

{
  if ((BIGNUM *)*param_1 != (BIGNUM *)0x0) {
    BN_free((BIGNUM *)*param_1);
  }
  *param_1 = 0;
  return;
}

