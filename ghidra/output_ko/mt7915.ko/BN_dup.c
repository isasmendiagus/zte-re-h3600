// module: mt7915.ko
// function: BN_dup @ 0x20d718
// size: 116 bytes
//

BIGNUM * BN_dup(BIGNUM *a)

{
  BIGNUM *a_00;
  BIGNUM *pBVar1;
  
  if (a == (BIGNUM *)0x0) {
LAB_0020d778:
    a_00 = (BIGNUM *)0x0;
  }
  else {
    if ((a->flags & 8U) == 0) {
      a_00 = BN_new();
      if (a_00 == (BIGNUM *)0x0) goto LAB_0020d778;
    }
    else {
      a_00 = BN_new();
      if (a_00 == (BIGNUM *)0x0) goto LAB_0020d778;
      a_00->flags = a_00->flags | 8;
    }
    pBVar1 = BN_copy(a_00,a);
    if (pBVar1 == (BIGNUM *)0x0) {
      BN_free(a_00);
      a_00 = (BIGNUM *)0x0;
    }
  }
  return a_00;
}

