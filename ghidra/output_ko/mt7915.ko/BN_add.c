// module: mt7915.ko
// function: BN_add @ 0x210f88
// size: 200 bytes
//

int BN_add(BIGNUM *r,BIGNUM *a,BIGNUM *b)

{
  int iVar1;
  BIGNUM *b_00;
  int iVar2;
  
  if (r != (BIGNUM *)0x0 && (b != (BIGNUM *)0x0 && a != (BIGNUM *)0x0)) {
    iVar2 = a->neg;
    if (iVar2 == b->neg) {
      iVar1 = BN_uadd(r,a,b);
      r->neg = iVar2;
      return iVar1;
    }
    b_00 = b;
    if (iVar2 != 0) {
      b_00 = a;
      a = b;
    }
    iVar2 = FUN_0020cef8(a,b_00);
    if (iVar2 < 0) {
      iVar2 = BN_usub(r,b_00,a);
      if (iVar2 != 0) {
        r->neg = 1;
        return 1;
      }
    }
    else {
      iVar2 = BN_usub(r,a,b_00);
      if (iVar2 != 0) {
        r->neg = 0;
        return 1;
      }
    }
  }
  return 0;
}

