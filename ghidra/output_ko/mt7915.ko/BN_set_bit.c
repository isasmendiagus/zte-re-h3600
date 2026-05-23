// module: mt7915.ko
// function: BN_set_bit @ 0x20da84
// size: 168 bytes
//

int BN_set_bit(BIGNUM *a,int n)

{
  int iVar1;
  BIGNUM *pBVar2;
  int iVar3;
  int iVar4;
  int words;
  
  if (n < 0) {
    return 0;
  }
  iVar1 = n >> 5;
  iVar4 = a->top;
  if (iVar4 <= iVar1) {
    words = iVar1 + 1;
    if (a == (BIGNUM *)0x0) {
      return 0;
    }
    if (a->dmax < words) {
      pBVar2 = bn_expand2(a,words);
      if (pBVar2 == (BIGNUM *)0x0) {
        return 0;
      }
      iVar4 = a->top;
    }
    if (iVar4 < words) {
      iVar3 = iVar4 << 2;
      do {
        iVar4 = iVar4 + 1;
        *(undefined4 *)((int)a->d + iVar3) = 0;
        iVar3 = iVar3 + 4;
      } while (iVar4 != words);
    }
    a->top = words;
  }
  a->d[iVar1] = a->d[iVar1] | 1 << (n & 0x1fU);
  return 1;
}

