// module: mt7915.ko
// function: Bignum_Bin2BI @ 0x20c380
// size: 56 bytes
//

void Bignum_Bin2BI(uchar *param_1,int param_2,undefined4 *param_3)

{
  BIGNUM *pBVar1;
  
  if ((BIGNUM *)*param_3 != (BIGNUM *)0x0) {
    BN_free((BIGNUM *)*param_3);
  }
  pBVar1 = BN_bin2bn(param_1,param_2,(BIGNUM *)0x0);
  *param_3 = pBVar1;
  return;
}

