// module: mt7915.ko
// function: BN_exp @ 0x216198
// size: 408 bytes
//

int BN_exp(BIGNUM *r,BIGNUM *a,BIGNUM *p,BN_CTX *ctx)

{
  BIGNUM *a_00;
  BIGNUM *pBVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  BIGNUM *pBVar5;
  uint uVar6;
  
  if (((p != (BIGNUM *)0x0) && ((p->flags & 4U) != 0)) ||
     ((a != (BIGNUM *)0x0 && ((a->flags & 4U) != 0)))) {
    return 0;
  }
  BN_CTX_start(ctx);
  pBVar5 = r;
  if (r == a || r == p) {
    pBVar5 = BN_CTX_get(ctx);
  }
  a_00 = BN_CTX_get(ctx);
  if ((pBVar5 != (BIGNUM *)0x0 && a_00 != (BIGNUM *)0x0) &&
     (pBVar1 = BN_copy(a_00,a), pBVar1 != (BIGNUM *)0x0)) {
    iVar2 = BN_num_bits(p);
    if ((p == (BIGNUM *)0x0) || ((p->top < 1 || ((*p->d & 1) == 0)))) {
      pBVar1 = (BIGNUM *)BN_set_word(pBVar5,1);
    }
    else {
      pBVar1 = BN_copy(pBVar5,a);
    }
    if (pBVar1 != (BIGNUM *)0x0) {
      if (1 < iVar2) {
        iVar4 = 1;
        do {
          iVar3 = FUN_0020f4cc(a_00,a_00,ctx);
          if ((iVar3 == 0) ||
             (((iVar3 = iVar4 + 1, p != (BIGNUM *)0x0 && -1 < iVar4 &&
               (iVar4 = FUN_0020cf74(p,iVar4), iVar4 != 0)) &&
              (iVar4 = FUN_00212078(pBVar5,pBVar5,a_00,ctx), iVar4 == 0)))) goto LAB_0021620c;
          iVar4 = iVar3;
        } while (iVar3 != iVar2);
      }
      if (r == pBVar5) {
        uVar6 = 1;
      }
      else {
        pBVar5 = BN_copy(r,pBVar5);
        uVar6 = (uint)(pBVar5 != (BIGNUM *)0x0);
      }
      goto LAB_00216210;
    }
  }
LAB_0021620c:
  uVar6 = 0;
LAB_00216210:
  BN_CTX_end(ctx);
  return uVar6;
}

