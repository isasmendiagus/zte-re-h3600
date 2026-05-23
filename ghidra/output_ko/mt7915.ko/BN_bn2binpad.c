// module: mt7915.ko
// function: BN_bn2binpad @ 0x20d8b4
// size: 204 bytes
//

int BN_bn2binpad(BIGNUM *param_1,undefined1 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (param_3 < 0) {
    return -1;
  }
  iVar1 = BN_num_bits(param_1);
  iVar2 = iVar1 + 7;
  if (iVar2 < 0) {
    iVar2 = iVar1 + 0xe;
  }
  iVar2 = iVar2 >> 3;
  iVar1 = iVar2;
  if (param_3 != -1) {
    if (param_3 < iVar2) {
      return -1;
    }
    iVar1 = param_3;
    if (iVar2 < param_3) {
      param_3 = param_3 - iVar2;
      if (param_3 != 0) {
        __memzero(param_2,param_3);
      }
      param_2 = param_2 + param_3;
    }
  }
  iVar3 = iVar2 + -1;
  if (iVar2 != 0) {
    do {
      iVar2 = iVar3 + 3;
      if (-1 < iVar3) {
        iVar2 = iVar3;
      }
      iVar4 = iVar3 + -1;
      *param_2 = (char)(param_1->d[iVar2 >> 2] >> ((iVar3 % 4) * 8 & 0xffU));
      iVar3 = iVar4;
      param_2 = param_2 + 1;
    } while (iVar4 != -1);
  }
  return iVar1;
}

