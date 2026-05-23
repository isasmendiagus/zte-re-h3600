// module: mt7915.ko
// function: Bignum_Montgomery_ExpMod @ 0x20c8d0
// size: 100 bytes
//

void Bignum_Montgomery_ExpMod(BIGNUM *param_1,BIGNUM *param_2,BIGNUM *param_3,int *param_4)

{
  BN_CTX *ctx;
  BIGNUM *r;
  
  ctx = BN_CTX_new();
  r = (BIGNUM *)*param_4;
  if (r == (BIGNUM *)0x0) {
    r = BN_new();
    *param_4 = (int)r;
  }
  BN_mod_exp_mont(r,param_1,param_2,param_3,ctx,(BN_MONT_CTX *)0x0);
  BN_CTX_free(ctx);
  return;
}

