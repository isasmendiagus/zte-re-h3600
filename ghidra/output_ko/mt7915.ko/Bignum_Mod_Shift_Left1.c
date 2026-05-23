// module: mt7915.ko
// function: Bignum_Mod_Shift_Left1 @ 0x20c7d4
// size: 24 bytes
//

void Bignum_Mod_Shift_Left1(BIGNUM *param_1,BIGNUM *param_2,undefined4 *param_3)

{
  BN_mod_lshift1_quick((BIGNUM *)*param_3,param_1,param_2);
  return;
}

