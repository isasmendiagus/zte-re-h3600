// module: mt7915.ko
// function: BN_rshift @ 0x210bec
// size: 344 bytes
//

int BN_rshift(BIGNUM *r,BIGNUM *a,int n)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  BIGNUM *pBVar5;
  ulong *puVar6;
  uint uVar7;
  uint *puVar8;
  uint *puVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  
  if (n < 0) {
    return 0;
  }
  if (a == (BIGNUM *)0x0 || r == (BIGNUM *)0x0) {
    return 0;
  }
  iVar10 = a->top;
  iVar1 = n >> 5;
  iVar11 = 0;
  if (iVar10 != 0) {
    iVar11 = iVar1 - iVar10;
  }
  if (iVar11 < 0 == (iVar10 != 0 && SBORROW4(iVar1,iVar10))) {
    r->top = 0;
    r->neg = 0;
    return 1;
  }
  iVar3 = BN_num_bits(a);
  iVar11 = (iVar3 - n) + 0x1f;
  if (iVar11 < 0) {
    iVar11 = (iVar3 - n) + 0x3e;
  }
  iVar11 = iVar11 >> 5;
  if (r == a) {
    if (n == 0) {
      return 1;
    }
  }
  else {
    if ((r->dmax < iVar11) && (pBVar5 = bn_expand2(r,iVar11), pBVar5 == (BIGNUM *)0x0)) {
      return 0;
    }
    r->neg = a->neg;
    iVar10 = a->top;
  }
  puVar6 = a->d;
  uVar7 = n & 0x1f;
  iVar10 = iVar10 - iVar1;
  r->top = iVar11;
  puVar4 = puVar6 + iVar1;
  puVar9 = r->d;
  if (uVar7 == 0) {
    if (iVar10 == 0) goto LAB_00210d14;
    puVar9 = puVar9 + -1;
    do {
      iVar10 = iVar10 + -1;
      puVar9 = puVar9 + 1;
      *puVar9 = *puVar4;
      puVar4 = puVar4 + 1;
    } while (iVar10 != 0);
  }
  else {
    iVar11 = iVar10 + -1;
    uVar12 = puVar6[iVar1];
    if (iVar11 != 0) {
      puVar8 = puVar9;
      do {
        puVar4 = puVar4 + 1;
        uVar2 = uVar12 >> uVar7;
        uVar12 = *puVar4;
        iVar11 = iVar11 + -1;
        *puVar8 = uVar2 | uVar12 << (0x20 - uVar7 & 0xff);
        puVar8 = puVar8 + 1;
      } while (iVar11 != 0);
      puVar9 = puVar9 + iVar10 + 0x3fffffff;
    }
    if (uVar12 >> uVar7 != 0) {
      *puVar9 = uVar12 >> uVar7;
    }
  }
  iVar11 = r->top;
LAB_00210d14:
  if (iVar11 != 0) {
    return 1;
  }
  r->neg = 0;
  return 1;
}

