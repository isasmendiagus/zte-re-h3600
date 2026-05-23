// module: mt7915.ko
// function: BN_mul_word @ 0x2115dc
// size: 172 bytes
//

int BN_mul_word(BIGNUM *a,ulong w)

{
  ulong uVar1;
  BIGNUM *pBVar2;
  int words;
  int iVar3;
  
  if (a->top != 0) {
    if (w == 0) {
      if (a != (BIGNUM *)0x0) {
        a->top = 0;
        a->neg = 0;
        return 1;
      }
    }
    else {
      uVar1 = FUN_0020cb1c(a->d,a->d,a->top,w);
      if (uVar1 != 0) {
        iVar3 = a->top;
        words = iVar3 + 1;
        if (a == (BIGNUM *)0x0) {
          return 0;
        }
        if (a->dmax < words) {
          pBVar2 = bn_expand2(a,words);
          if (pBVar2 == (BIGNUM *)0x0) {
            return 0;
          }
          iVar3 = a->top;
          words = iVar3 + 1;
        }
        a->top = words;
        a->d[iVar3] = uVar1;
        return 1;
      }
    }
  }
  return 1;
}

