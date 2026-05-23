// module: mt7915.ko
// function: BN_set_word @ 0x20d85c
// size: 88 bytes
//

int BN_set_word(BIGNUM *a,ulong w)

{
  BIGNUM *pBVar1;
  
  if ((a != (BIGNUM *)0x0) && ((0 < a->dmax || (pBVar1 = bn_expand2(a,1), pBVar1 != (BIGNUM *)0x0)))
     ) {
    a->neg = 0;
    *a->d = w;
    a->top = (uint)(w != 0);
    return 1;
  }
  return 0;
}

