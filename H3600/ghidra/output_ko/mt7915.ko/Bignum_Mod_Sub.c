// module: mt7915.ko
// function: Bignum_Mod_Sub @ 0x20c618
// size: 92 bytes
//

void Bignum_Mod_Sub(BIGNUM *param_1,BIGNUM *param_2,BIGNUM *param_3,int *param_4)

{
  BN_CTX *ctx;
  BIGNUM *r;
  
  ctx = BN_CTX_new();
  r = (BIGNUM *)*param_4;
  if (r == (BIGNUM *)0x0) {
    r = BN_new();
    *param_4 = (int)r;
  }
  BN_mod_sub(r,param_1,param_2,param_3,ctx);
  BN_CTX_free(ctx);
  return;
}

