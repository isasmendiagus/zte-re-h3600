// module: mt7915.ko
// function: BN_sub @ 0x211050
// size: 292 bytes
//

int BN_sub(BIGNUM *r,BIGNUM *a,BIGNUM *b)

{
  int iVar1;
  BIGNUM *pBVar2;
  BIGNUM *a_00;
  BIGNUM *b_00;
  int iVar3;
  
  if (a == (BIGNUM *)0x0 || (r == (BIGNUM *)0x0 || b == (BIGNUM *)0x0)) {
    return 0;
  }
  if (a->neg == 0) {
    a_00 = a;
    b_00 = b;
    if (b->neg != 0) {
      iVar3 = 0;
      goto LAB_0021109c;
    }
  }
  else {
    a_00 = b;
    b_00 = a;
    if (b->neg == 0) {
      iVar3 = 1;
LAB_0021109c:
      iVar1 = BN_uadd(r,a,b);
      if (iVar1 == 0) {
        return 0;
      }
      r->neg = iVar3;
      return 1;
    }
  }
  iVar3 = a_00->top;
  if (a_00->top < b_00->top) {
    iVar3 = b_00->top;
  }
  if ((iVar3 <= r->dmax) || (pBVar2 = bn_expand2(r,iVar3), pBVar2 != (BIGNUM *)0x0)) {
    iVar3 = FUN_0020cef8(a_00,b_00);
    if (iVar3 < 0) {
      iVar3 = BN_usub(r,b_00,a_00);
      if (iVar3 != 0) {
        r->neg = 1;
        return 1;
      }
    }
    else {
      iVar3 = BN_usub(r,a_00,b_00);
      if (iVar3 != 0) {
        r->neg = 0;
        return 1;
      }
    }
  }
  return 0;
}

