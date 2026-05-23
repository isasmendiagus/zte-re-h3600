// module: mt7915.ko
// function: Bignum_BI2Bin_with_pad @ 0x20c31c
// size: 100 bytes
//

void Bignum_BI2Bin_with_pad(BIGNUM *param_1,int param_2,int *param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = BN_num_bits(param_1);
  iVar2 = iVar1 + 7;
  if (iVar2 < 0) {
    iVar2 = iVar1 + 0xe;
  }
  if ((uint)(iVar2 >> 3) < param_4) {
    iVar1 = param_4 - (iVar2 >> 3);
    if (iVar1 != 0) {
      __memzero(param_2,iVar1);
    }
  }
  else {
    iVar1 = 0;
  }
  Bignum_BI2Bin(param_1,param_2 + iVar1,param_3);
  *param_3 = *param_3 + iVar1;
  return;
}

