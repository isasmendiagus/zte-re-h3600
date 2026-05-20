// module: mt7915.ko
// function: BigInteger_BI2Bin_with_pad @ 0x1fb46c
// size: 92 bytes
//

void BigInteger_BI2Bin_with_pad(int param_1,int param_2,int *param_3,uint param_4)

{
  int iVar1;
  
  if (param_1 != 0) {
    if (param_4 < *(uint *)(param_1 + 0x18)) {
      iVar1 = 0;
    }
    else {
      iVar1 = param_4 - *(uint *)(param_1 + 0x18);
      if (iVar1 != 0) {
        __memzero(param_2,iVar1,param_3,param_4,param_4);
      }
    }
    BigInteger_BI2Bin(param_1,param_2 + iVar1,param_3);
    *param_3 = *param_3 + iVar1;
    return;
  }
  return;
}

