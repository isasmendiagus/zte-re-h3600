// module: mt7915.ko
// function: BN_cmp @ 0x20d998
// size: 236 bytes
//

int BN_cmp(BIGNUM *a,BIGNUM *b)

{
  uint uVar1;
  ulong *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  ulong *puVar6;
  uint uVar7;
  bool bVar8;
  
  if (b == (BIGNUM *)0x0 || a == (BIGNUM *)0x0) {
    if (a == (BIGNUM *)0x0) {
      return (uint)(b != (BIGNUM *)0x0);
    }
    return -1;
  }
  iVar3 = a->neg;
  if (iVar3 != b->neg) {
    if (iVar3 == 0) {
      iVar3 = 1;
    }
    else {
      iVar3 = -1;
    }
    return iVar3;
  }
  iVar4 = a->top;
  if (iVar3 == 0) {
    iVar3 = -1;
    iVar5 = 1;
  }
  else {
    iVar3 = 1;
    iVar5 = -1;
  }
  if (b->top < iVar4) {
    return iVar5;
  }
  if (b->top <= iVar4) {
    iVar4 = iVar4 + -1;
    if (iVar4 < 0) {
      return 0;
    }
    uVar7 = a->d[iVar4];
    uVar1 = b->d[iVar4];
    if (uVar1 < uVar7) {
      return iVar5;
    }
    if (uVar1 <= uVar7) {
      puVar6 = a->d + iVar4;
      puVar2 = b->d + iVar4;
      do {
        bVar8 = iVar4 == 0;
        iVar4 = iVar4 + -1;
        if (bVar8) {
          return 0;
        }
        puVar6 = puVar6 + -1;
        puVar2 = puVar2 + -1;
        if (*puVar2 < *puVar6) {
          return iVar5;
        }
      } while (*puVar2 <= *puVar6);
    }
  }
  return iVar3;
}

