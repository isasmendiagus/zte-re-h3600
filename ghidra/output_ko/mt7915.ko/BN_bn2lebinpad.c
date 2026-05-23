// module: mt7915.ko
// function: BN_bn2lebinpad @ 0x20d8d0
// size: 176 bytes
//

int BN_bn2lebinpad(BIGNUM *param_1,int param_2,int param_3)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = BN_num_bits(param_1);
  iVar3 = iVar1 + 7;
  if (iVar3 < 0) {
    iVar3 = iVar1 + 0xe;
  }
  iVar3 = iVar3 >> 3;
  if (iVar3 <= param_3) {
    if ((iVar3 < param_3) && (param_3 != iVar3)) {
      __memzero(param_2 + iVar3);
    }
    puVar2 = (undefined1 *)(param_2 + iVar3);
    iVar1 = iVar3 + -1;
    if (iVar3 != 0) {
      do {
        iVar3 = iVar1 + 3;
        if (-1 < iVar1) {
          iVar3 = iVar1;
        }
        iVar4 = iVar1 + -1;
        puVar2 = puVar2 + -1;
        *puVar2 = (char)(param_1->d[iVar3 >> 2] >> ((iVar1 % 4) * 8 & 0xffU));
        iVar1 = iVar4;
      } while (iVar4 != -1);
    }
    return param_3;
  }
  return -1;
}

