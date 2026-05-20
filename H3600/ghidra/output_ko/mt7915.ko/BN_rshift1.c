// module: mt7915.ko
// function: BN_rshift1 @ 0x2108f0
// size: 248 bytes
//

int BN_rshift1(BIGNUM *r,BIGNUM *a)

{
  BIGNUM *pBVar1;
  ulong *puVar2;
  uint uVar3;
  ulong *puVar4;
  int iVar5;
  int words;
  int iVar6;
  uint uVar7;
  ulong *puVar8;
  
  if (a == (BIGNUM *)0x0 || r == (BIGNUM *)0x0) {
    return 0;
  }
  iVar5 = a->top;
  if (iVar5 == 0) {
    r->top = 0;
    r->neg = 0;
    return 1;
  }
  puVar4 = a->d;
  iVar6 = iVar5 + 0x3fffffff;
  words = iVar5;
  if (puVar4[iVar6] == 1) {
    words = iVar5 + -1;
  }
  if (r != a) {
    if ((r->dmax < words) && (pBVar1 = bn_expand2(r,words), pBVar1 == (BIGNUM *)0x0)) {
      return 0;
    }
    r->neg = a->neg;
  }
  puVar8 = r->d;
  if ((puVar4[iVar6] & 1) == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = 0x80000000;
  }
  puVar2 = (ulong *)(puVar4[iVar6] >> 1);
  if (puVar2 != (ulong *)0x0) {
    puVar8[iVar6] = (ulong)puVar2;
  }
  if (iVar5 != 1 && -1 < iVar5 + -1) {
    puVar8 = puVar8 + iVar6;
    puVar2 = puVar4 + iVar6;
  }
  if (0 < iVar5 + -1) {
    do {
      puVar2 = puVar2 + -1;
      uVar7 = *puVar2;
      puVar8 = puVar8 + -1;
      *puVar8 = uVar3 | uVar7 >> 1;
      if ((uVar7 & 1) == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = 0x80000000;
      }
    } while (puVar2 != puVar4);
  }
  r->top = words;
  if (words != 0) {
    return 1;
  }
  r->neg = 0;
  return 1;
}

