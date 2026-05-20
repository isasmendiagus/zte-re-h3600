// module: mt7915.ko
// function: Bignum_Init @ 0x20c288
// size: 32 bytes
//

void Bignum_Init(int *param_1)

{
  BIGNUM *pBVar1;
  
  if (*param_1 != 0) {
    return;
  }
  pBVar1 = BN_new();
  *param_1 = (int)pBVar1;
  return;
}

