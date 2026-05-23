// module: mt7915.ko
// function: Bignum_Mod_Shift_Left @ 0x20c7ec
// size: 36 bytes
//

void Bignum_Mod_Shift_Left(BIGNUM *param_1,int param_2,BIGNUM *param_3,undefined4 *param_4)

{
  BN_mod_lshift_quick((BIGNUM *)*param_4,param_1,param_2,param_3);
  return;
}

