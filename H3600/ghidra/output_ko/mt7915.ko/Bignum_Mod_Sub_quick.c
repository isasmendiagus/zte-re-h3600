// module: mt7915.ko
// function: Bignum_Mod_Sub_quick @ 0x20c6c0
// size: 76 bytes
//

void Bignum_Mod_Sub_quick(BIGNUM *param_1,BIGNUM *param_2,BIGNUM *param_3,int *param_4)

{
  BIGNUM *r;
  
  r = (BIGNUM *)*param_4;
  if (r == (BIGNUM *)0x0) {
    r = BN_new();
    *param_4 = (int)r;
  }
  BN_mod_sub_quick(r,param_1,param_2,param_3);
  return;
}

