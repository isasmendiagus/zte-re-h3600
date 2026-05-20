// module: mt7915.ko
// function: Bignum_Mod @ 0x20c488
// size: 92 bytes
//

void Bignum_Mod(BIGNUM *param_1,BIGNUM *param_2,int *param_3)

{
  BN_CTX *ctx;
  BIGNUM *rem;
  
  ctx = BN_CTX_new();
  rem = (BIGNUM *)*param_3;
  if (rem == (BIGNUM *)0x0) {
    rem = BN_new();
    *param_3 = (int)rem;
  }
  BN_div((BIGNUM *)0x0,rem,param_1,param_2,ctx);
  BN_CTX_free(ctx);
  return;
}

