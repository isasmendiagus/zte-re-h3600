// module: mt7915.ko
// function: BN_kronecker @ 0x216348
// size: 732 bytes
//

int BN_kronecker(BIGNUM *a,BIGNUM *b,BN_CTX *ctx)

{
  BIGNUM *a_00;
  BIGNUM *a_01;
  BIGNUM *pBVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  BN_CTX_start(ctx);
  a_00 = BN_CTX_get(ctx);
  a_01 = BN_CTX_get(ctx);
  if (a_00 == (BIGNUM *)0x0 || a_01 == (BIGNUM *)0x0) {
    uVar3 = 0xfffffffe;
  }
  else {
    uVar3 = 0;
    pBVar1 = BN_copy(a_00,a);
    if ((pBVar1 == (BIGNUM *)0x0) || (pBVar1 = BN_copy(a_01,b), pBVar1 == (BIGNUM *)0x0)) {
LAB_002163a0:
      BN_CTX_end(ctx);
      return -2;
    }
    if (a_01->top == 0) {
      if (a_00->top == 1) {
        uVar3 = (uint)(*a_00->d == 1);
      }
      else {
        uVar3 = 0;
      }
    }
    else {
      if ((a_00->top < 1) || ((*a_00->d & 1) == 0)) {
        if ((a_01->top < 1) || ((*a_01->d & 1) == 0)) {
          BN_CTX_end(ctx);
          return 0;
        }
        uVar3 = 0;
      }
      while (((int)uVar3 < 0 || (iVar2 = FUN_0020cf74(a_01,uVar3), iVar2 == 0))) {
        uVar3 = uVar3 + 1;
      }
      iVar2 = BN_rshift(a_01,a_01,uVar3);
      if (iVar2 == 0) goto LAB_002163a0;
      if ((uVar3 & 1) == 0) {
        uVar3 = 1;
      }
      else {
        if (a_00->top == 0) {
          uVar3 = 0;
        }
        else {
          uVar3 = *a_00->d & 7;
        }
        uVar3 = *(uint *)(&DAT_002a2008 + uVar3 * 4);
      }
      if (a_01->neg != 0) {
        a_01->neg = 0;
        uVar4 = (uint)(a_00->neg != 0);
        uVar3 = (-uVar4 ^ uVar3) + uVar4;
      }
      iVar2 = a_00->top;
      while (pBVar1 = a_00, iVar2 != 0) {
        uVar4 = 0;
        while (((int)uVar4 < 0 || (iVar2 = FUN_0020cf74(pBVar1,uVar4), iVar2 == 0))) {
          uVar4 = uVar4 + 1;
        }
        iVar2 = BN_rshift(pBVar1,pBVar1,uVar4);
        if (iVar2 == 0) goto LAB_002163a0;
        if ((uVar4 & 1) != 0) {
          if (a_01->top == 0) {
            uVar4 = 0;
          }
          else {
            uVar4 = *a_01->d & 7;
          }
          uVar3 = *(int *)(&DAT_002a2008 + uVar4 * 4) * uVar3;
        }
        if (pBVar1->neg == 0) {
          uVar4 = 0;
          if (pBVar1->top != 0) {
            uVar4 = *pBVar1->d;
          }
        }
        else if (pBVar1->top == 0) {
          uVar4 = 0xffffffff;
        }
        else {
          uVar4 = ~*pBVar1->d;
        }
        if (a_01->top != 0) {
          uVar4 = (uint)((*a_01->d & 2 & uVar4) != 0);
          uVar3 = (-uVar4 ^ uVar3) + uVar4;
        }
        iVar2 = BN_nnmod(a_01,a_01,pBVar1,ctx);
        if (iVar2 == 0) goto LAB_002163a0;
        pBVar1->neg = 0;
        iVar2 = a_01->top;
        a_00 = a_01;
        a_01 = pBVar1;
      }
      iVar2 = BN_is_one(a_01);
      if (iVar2 == 0) {
        uVar3 = 0;
      }
    }
  }
  BN_CTX_end(ctx);
  return uVar3;
}

