// module: mt7915.ko
// function: BN_add_word @ 0x2114e8
// size: 244 bytes
//

int BN_add_word(BIGNUM *a,ulong w)

{
  BIGNUM *pBVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if ((w != 0) && (a != (BIGNUM *)0x0)) {
    iVar3 = a->top;
    if (iVar3 == 0) {
      iVar3 = BN_set_word(a,w);
      return iVar3;
    }
    if (a->neg != 0) {
      a->neg = 0;
      iVar3 = BN_sub_word(a,w);
      if (a->top != 0) {
        a->neg = (uint)(a->neg == 0);
      }
      return iVar3;
    }
    iVar2 = 0;
    while (iVar2 < iVar3) {
      uVar4 = w + a->d[iVar2];
      a->d[iVar2] = uVar4;
      iVar2 = iVar2 + 1;
      if (w <= uVar4) {
        return 1;
      }
      w = 1;
      iVar3 = a->top;
    }
    if (iVar3 == iVar2) {
      iVar2 = iVar2 + 1;
      if (a->dmax < iVar2) {
        pBVar1 = bn_expand2(a,iVar2);
        if (pBVar1 == (BIGNUM *)0x0) {
          return 0;
        }
        iVar2 = a->top + 1;
      }
      a->top = iVar2;
      a->d[iVar3] = w;
      return 1;
    }
  }
  return 1;
}

