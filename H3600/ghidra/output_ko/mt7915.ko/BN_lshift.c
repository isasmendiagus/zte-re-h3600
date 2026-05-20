// module: mt7915.ko
// function: BN_lshift @ 0x2109e8
// size: 300 bytes
//

int BN_lshift(BIGNUM *r,BIGNUM *a,int n)

{
  uint uVar1;
  ulong *puVar2;
  BIGNUM *pBVar3;
  uint uVar4;
  int iVar5;
  ulong *puVar6;
  uint uVar7;
  ulong *puVar8;
  int iVar9;
  
  if (n < 0) {
    return 0;
  }
  uVar1 = n >> 5;
  if (((a != (BIGNUM *)0x0) && (iVar5 = uVar1 + a->top + 1, r != (BIGNUM *)0x0)) &&
     ((iVar5 <= r->dmax || (pBVar3 = bn_expand2(r,iVar5), pBVar3 != (BIGNUM *)0x0)))) {
    uVar4 = n & 0x1f;
    puVar2 = r->d;
    r->neg = a->neg;
    puVar8 = a->d;
    puVar2[uVar1 + a->top] = 0;
    if (uVar4 == 0) {
      iVar5 = a->top + -1;
      if (-1 < iVar5) {
        puVar6 = puVar8 + a->top;
        puVar2 = puVar2 + uVar1 + iVar5;
        do {
          puVar6 = puVar6 + -1;
          *puVar2 = *puVar6;
          puVar2 = puVar2 + -1;
        } while (puVar6 != puVar8);
      }
    }
    else {
      iVar9 = a->top;
      iVar5 = iVar9 + -1;
      if (-1 < iVar5) {
        puVar8 = puVar8 + iVar9;
        puVar2 = puVar2 + uVar1 + iVar9;
        do {
          puVar8 = puVar8 + -1;
          uVar7 = *puVar8;
          iVar5 = iVar5 + -1;
          *puVar2 = *puVar2 | uVar7 >> (0x20 - uVar4 & 0xff);
          puVar2 = puVar2 + -1;
          *puVar2 = uVar7 << uVar4;
        } while (iVar5 != -1);
      }
    }
    if ((uVar1 & 0x3fffffff) != 0) {
      __memzero();
    }
    r->top = uVar1 + a->top + 1;
    bn_correct_top(r);
    return 1;
  }
  return 0;
}

