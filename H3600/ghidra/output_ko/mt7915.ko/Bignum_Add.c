// module: mt7915.ko
// function: Bignum_Add @ 0x20c3e8
// size: 80 bytes
//

void Bignum_Add(BIGNUM *param_1,BIGNUM *param_2,undefined4 *param_3)

{
  BIGNUM *r;
  
  if ((BIGNUM *)*param_3 != (BIGNUM *)0x0) {
    BN_add((BIGNUM *)*param_3,param_1,param_2);
    return;
  }
  r = BN_new();
  *param_3 = r;
  BN_add(r,param_1,param_2);
  return;
}

