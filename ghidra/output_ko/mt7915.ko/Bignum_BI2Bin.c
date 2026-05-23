// module: mt7915.ko
// function: Bignum_BI2Bin @ 0x20c2e8
// size: 52 bytes
//

void Bignum_BI2Bin(BIGNUM *param_1,uchar *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = BN_num_bits(param_1);
  iVar2 = iVar1 + 7;
  if (iVar2 < 0) {
    iVar2 = iVar1 + 0xe;
  }
  *param_3 = iVar2 >> 3;
  BN_bn2bin(param_1,param_2);
  return;
}

