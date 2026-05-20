// module: mt7915.ko
// function: Bignum_Mod_Sqrt @ 0x20c760
// size: 76 bytes
//

void Bignum_Mod_Sqrt(BIGNUM *param_1,BIGNUM *param_2,int *param_3)

{
  BN_CTX *ctx;
  BIGNUM *ret;
  
  ctx = BN_CTX_new();
  ret = (BIGNUM *)*param_3;
  if (ret == (BIGNUM *)0x0) {
    ret = BN_new();
    *param_3 = (int)ret;
  }
  BN_mod_sqrt(ret,param_1,param_2,ctx);
  BN_CTX_free(ctx);
  return;
}

