// module: mt7915.ko
// function: Bignum_Mod_Square @ 0x20c570
// size: 76 bytes
//

void Bignum_Mod_Square(BIGNUM *param_1,BIGNUM *param_2,int *param_3)

{
  BN_CTX *ctx;
  BIGNUM *r;
  
  ctx = BN_CTX_new();
  r = (BIGNUM *)*param_3;
  if (r == (BIGNUM *)0x0) {
    r = BN_new();
    *param_3 = (int)r;
  }
  BN_mod_sqr(r,param_1,param_2,ctx);
  BN_CTX_free(ctx);
  return;
}

