// module: mt7915.ko
// function: BN_mod_inverse @ 0x214878
// size: 28 bytes
//

BIGNUM * BN_mod_inverse(BIGNUM *ret,BIGNUM *a,BIGNUM *n,BN_CTX *ctx)

{
  BIGNUM *pBVar1;
  
  pBVar1 = (BIGNUM *)int_bn_mod_inverse();
  return pBVar1;
}

