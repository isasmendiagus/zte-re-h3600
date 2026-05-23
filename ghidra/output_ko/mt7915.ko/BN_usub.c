// module: mt7915.ko
// function: BN_usub @ 0x210e5c
// size: 216 bytes
//

int BN_usub(BIGNUM *r,BIGNUM *a,BIGNUM *b)

{
  uint uVar1;
  BIGNUM *pBVar2;
  ulong uVar3;
  int iVar4;
  ulong *puVar5;
  ulong *puVar6;
  int words;
  int iVar7;
  
  if (r == (BIGNUM *)0x0 || (b == (BIGNUM *)0x0 || a == (BIGNUM *)0x0)) {
    return 0;
  }
  words = a->top;
  iVar7 = b->top;
  iVar4 = words - iVar7;
  if ((-1 < iVar4) &&
     ((words <= r->dmax || (pBVar2 = bn_expand2(r,words), pBVar2 != (BIGNUM *)0x0)))) {
    puVar6 = a->d;
    puVar5 = r->d;
    uVar1 = FUN_0020cd98(puVar5,puVar6,b->d,iVar7);
    puVar6 = puVar6 + iVar7;
    puVar5 = puVar5 + iVar7;
    for (; iVar4 != 0; iVar4 = iVar4 + -1) {
      uVar3 = *puVar6 - uVar1;
      if (*puVar6 == 0) {
        uVar1 = uVar1 & 1;
      }
      else {
        uVar1 = 0;
      }
      *puVar5 = uVar3;
      puVar6 = puVar6 + 1;
      puVar5 = puVar5 + 1;
    }
    r->top = words;
    r->neg = 0;
    bn_correct_top(r);
    return 1;
  }
  return 0;
}

