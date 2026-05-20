// module: mt7915.ko
// function: Bignum_is_quadratic_residue @ 0x20c810
// size: 144 bytes
//

undefined1 Bignum_is_quadratic_residue(BIGNUM *param_1,BIGNUM *param_2)

{
  undefined1 uVar1;
  BN_CTX *ctx;
  BIGNUM *r;
  BIGNUM *local_24 [2];
  
  local_24[0] = (BIGNUM *)0x0;
  ctx = BN_CTX_new();
  r = BN_CTX_get(ctx);
  Bignum_Copy(param_2,local_24);
  BN_sub_word(local_24[0],1);
  Bignum_Shift_Right1(local_24[0],local_24);
  BN_mod_exp_mont(r,param_1,local_24[0],param_2,ctx,(BN_MONT_CTX *)0x0);
  uVar1 = BN_is_one(r);
  BN_CTX_free(ctx);
  BN_free(local_24[0]);
  return uVar1;
}

