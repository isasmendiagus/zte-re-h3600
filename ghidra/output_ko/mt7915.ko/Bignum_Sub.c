// module: mt7915.ko
// function: Bignum_Sub @ 0x20c438
// size: 80 bytes
//

void Bignum_Sub(BIGNUM *param_1,BIGNUM *param_2,undefined4 *param_3)

{
  BIGNUM *r;
  
  if ((BIGNUM *)*param_3 != (BIGNUM *)0x0) {
    BN_sub((BIGNUM *)*param_3,param_1,param_2);
    return;
  }
  r = BN_new();
  *param_3 = r;
  BN_sub(r,param_1,param_2);
  return;
}

