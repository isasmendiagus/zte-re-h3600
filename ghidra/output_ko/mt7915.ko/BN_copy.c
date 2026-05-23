// module: mt7915.ko
// function: BN_copy @ 0x20d60c
// size: 268 bytes
//

BIGNUM * BN_copy(BIGNUM *a,BIGNUM *b)

{
  int iVar1;
  ulong *puVar2;
  ulong *puVar3;
  BIGNUM *pBVar4;
  uint uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong *puVar8;
  ulong *puVar9;
  int iVar10;
  ulong uVar11;
  
  if (a == b) {
    return a;
  }
  if (b == (BIGNUM *)0x0 || a == (BIGNUM *)0x0) {
    return (BIGNUM *)0x0;
  }
  uVar5 = b->top;
  if (a->dmax < (int)uVar5) {
    pBVar4 = bn_expand2(a,uVar5);
    if (pBVar4 == (BIGNUM *)0x0) {
      return (BIGNUM *)0x0;
    }
    uVar5 = b->top;
  }
  iVar1 = (int)uVar5 >> 2;
  puVar8 = a->d;
  puVar9 = b->d;
  iVar10 = iVar1;
  puVar2 = puVar8;
  puVar3 = puVar9;
  if (0 < iVar1) {
    do {
      iVar10 = iVar10 + -1;
      uVar7 = puVar3[1];
      uVar11 = puVar3[3];
      uVar6 = puVar3[2];
      *puVar2 = *puVar3;
      puVar2[1] = uVar7;
      puVar2[3] = uVar11;
      puVar2[2] = uVar6;
      puVar2 = puVar2 + 4;
      puVar3 = puVar3 + 4;
    } while (iVar10 != 0);
    uVar5 = b->top;
    puVar8 = puVar8 + iVar1 * 4;
    puVar9 = puVar9 + iVar1 * 4;
  }
  uVar5 = uVar5 & 3;
  if (uVar5 == 2) {
LAB_0020d6e4:
    puVar8[1] = puVar9[1];
  }
  else {
    if (uVar5 == 3) {
      puVar8[2] = puVar9[2];
      goto LAB_0020d6e4;
    }
    if (uVar5 != 1) goto LAB_0020d6b0;
  }
  *puVar8 = *puVar9;
LAB_0020d6b0:
  if ((b->flags & 4U) != 0) {
    a->flags = a->flags | 4;
  }
  a->top = b->top;
  a->neg = b->neg;
  return a;
}

