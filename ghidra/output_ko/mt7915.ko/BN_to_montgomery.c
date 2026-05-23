// module: mt7915.ko
// function: BN_to_montgomery @ 0x213734
// size: 36 bytes
//

void BN_to_montgomery(BIGNUM *param_1,BIGNUM *param_2,BN_MONT_CTX *param_3,BN_CTX *param_4)

{
  BN_mod_mul_montgomery(param_1,param_2,&param_3->RR,param_3,param_4);
  return;
}

