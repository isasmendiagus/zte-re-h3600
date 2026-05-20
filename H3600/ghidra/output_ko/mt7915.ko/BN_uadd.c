// module: mt7915.ko
// function: BN_uadd @ 0x210d44
// size: 280 bytes
//

int BN_uadd(BIGNUM *r,BIGNUM *a,BIGNUM *b)

{
  int iVar1;
  ulong uVar2;
  BIGNUM *pBVar3;
  BIGNUM *pBVar4;
  ulong uVar5;
  int iVar6;
  int iVar7;
  ulong *puVar8;
  ulong *puVar9;
  int unaff_r8;
  int extraout_r12;
  ulong *puVar10;
  
  if (a != (BIGNUM *)0x0 && (r != (BIGNUM *)0x0 && b != (BIGNUM *)0x0)) {
    iVar6 = a->top;
    iVar1 = b->top;
    pBVar4 = b;
    if (iVar6 < iVar1) {
      pBVar4 = a;
      a = b;
    }
    iVar7 = iVar6;
    if (iVar6 < iVar1) {
      iVar7 = iVar1;
      unaff_r8 = iVar6;
    }
    if (iVar1 <= iVar6) {
      unaff_r8 = iVar1;
    }
    iVar1 = iVar7 - unaff_r8;
    if ((r->dmax < iVar7 + 1) && (pBVar3 = bn_expand2(r,iVar7 + 1), pBVar3 == (BIGNUM *)0x0)) {
      iVar1 = 0;
    }
    else {
      r->top = iVar7;
      puVar8 = a->d;
      puVar9 = r->d;
      uVar2 = FUN_0020cc88(puVar9,puVar8,pBVar4->d,unaff_r8);
      iVar6 = extraout_r12;
      if (iVar1 != 0) {
        iVar6 = iVar1;
      }
      puVar8 = puVar8 + unaff_r8;
      puVar9 = puVar9 + unaff_r8;
      puVar10 = puVar9;
      if (iVar1 != 0) {
        do {
          uVar5 = *puVar8;
          *puVar10 = uVar2 + uVar5;
          if (uVar2 + uVar5 == 0) {
            uVar2 = uVar2 & 1;
          }
          else {
            uVar2 = 0;
          }
          iVar6 = iVar6 + -1;
          puVar8 = puVar8 + 1;
          puVar10 = puVar10 + 1;
        } while (iVar6 != 0);
        puVar9 = puVar9 + iVar1;
      }
      *puVar9 = uVar2;
      iVar1 = 1;
      r->neg = 0;
      r->top = r->top + uVar2;
    }
    return iVar1;
  }
  return 0;
}

