// module: mt7915.ko
// function: Bignum_Get_rand_range @ 0x20c2d8
// size: 16 bytes
//

void Bignum_Get_rand_range(BIGNUM *param_1,BIGNUM *param_2)

{
  BN_rand_range(param_2,param_1);
  return;
}

