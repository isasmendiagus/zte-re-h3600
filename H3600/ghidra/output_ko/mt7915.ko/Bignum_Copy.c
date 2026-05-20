// module: mt7915.ko
// function: Bignum_Copy @ 0x20c3b8
// size: 44 bytes
//

void Bignum_Copy(BIGNUM *param_1,undefined4 *param_2)

{
  BIGNUM *pBVar1;
  
  if ((BIGNUM *)*param_2 != (BIGNUM *)0x0) {
    BN_free((BIGNUM *)*param_2);
  }
  pBVar1 = BN_dup(param_1);
  *param_2 = pBVar1;
  return;
}

