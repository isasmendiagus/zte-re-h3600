// module: mt7915.ko
// function: bn_wexpand @ 0x20e1c8
// size: 32 bytes
//

BIGNUM * bn_wexpand(BIGNUM *param_1,int param_2)

{
  BIGNUM *pBVar1;
  
  if ((param_1 != (BIGNUM *)0x0) && (param_1->dmax < param_2)) {
    pBVar1 = bn_expand2(param_1,param_2);
    return pBVar1;
  }
  return param_1;
}

