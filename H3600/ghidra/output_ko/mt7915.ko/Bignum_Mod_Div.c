// module: mt7915.ko
// function: Bignum_Mod_Div @ 0x20c70c
// size: 84 bytes
//

void Bignum_Mod_Div(undefined4 param_1,BIGNUM *param_2,BIGNUM *param_3,undefined4 param_4)

{
  BN_CTX *ctx;
  BIGNUM *ret;
  undefined4 uVar1;
  
  uVar1 = param_4;
  ctx = BN_CTX_new();
  ret = BN_CTX_get(ctx);
  BN_mod_inverse(ret,param_2,param_3,ctx);
  Bignum_Mod_Mul(param_1,ret,param_3,param_4,uVar1);
  BN_CTX_free(ctx);
  return;
}

