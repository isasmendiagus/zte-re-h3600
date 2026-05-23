// module: mt7915.ko
// function: Bignum_Shift_Right1 @ 0x20c7ac
// size: 40 bytes
//

void Bignum_Shift_Right1(BIGNUM *param_1,undefined4 *param_2)

{
  BN_copy((BIGNUM *)*param_2,param_1);
  BN_div_word((BIGNUM *)*param_2,2);
  return;
}

