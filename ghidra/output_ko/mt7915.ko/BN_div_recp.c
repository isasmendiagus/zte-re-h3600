// module: mt7915.ko
// function: BN_div_recp @ 0x213758
// size: 588 bytes
//

int BN_div_recp(BIGNUM *dv,BIGNUM *rem,BIGNUM *m,BN_RECP_CTX *recp,BN_CTX *ctx)

{
  BIGNUM *pBVar1;
  BIGNUM *a;
  int iVar2;
  int iVar3;
  int iVar4;
  
  BN_CTX_start(ctx);
  pBVar1 = BN_CTX_get(ctx);
  a = BN_CTX_get(ctx);
  if (dv == (BIGNUM *)0x0) {
    dv = BN_CTX_get(ctx);
  }
  if (rem == (BIGNUM *)0x0) {
    rem = BN_CTX_get(ctx);
  }
  if ((a != (BIGNUM *)0x0 && pBVar1 != (BIGNUM *)0x0) &&
     (rem != (BIGNUM *)0x0 && dv != (BIGNUM *)0x0)) {
    if ((m != (BIGNUM *)0x0 && recp != (BN_RECP_CTX *)0x0) &&
       (iVar4 = FUN_0020cef8(m,recp), iVar4 < 0)) {
      dv->top = 0;
      dv->neg = 0;
      pBVar1 = BN_copy(rem,m);
      iVar4 = 0;
      if (pBVar1 != (BIGNUM *)0x0) {
        BN_CTX_end(ctx);
        return 1;
      }
      goto LAB_002137bc;
    }
    iVar2 = BN_num_bits(m);
    iVar3 = recp->shift;
    iVar4 = recp->num_bits * 2;
    if (iVar2 < iVar4) {
      iVar2 = iVar4;
    }
    if (iVar3 != iVar2) {
      iVar3 = BN_reciprocal(&recp->Nr,&recp->N,iVar2,ctx);
      recp->shift = iVar3;
    }
    if ((((iVar3 != -1) && (iVar4 = BN_rshift(pBVar1,m,recp->num_bits), iVar4 != 0)) &&
        (&recp->Nr != (BIGNUM *)0x0)) &&
       (((iVar4 = FUN_00212078(a,pBVar1,&recp->Nr,ctx), iVar4 != 0 &&
         (iVar4 = BN_rshift(dv,a,iVar2 - recp->num_bits), iVar4 != 0)) &&
        ((dv->neg = 0, recp != (BN_RECP_CTX *)0x0 &&
         ((iVar4 = FUN_00212078(a,recp,dv,ctx), iVar4 != 0 && (iVar4 = BN_usub(rem,m,a), iVar4 != 0)
          ))))))) {
      rem->neg = 0;
      iVar4 = 4;
      do {
        iVar2 = FUN_0020cef8(rem,recp);
        if (iVar2 < 0) {
          iVar4 = 0;
          if (rem->top != 0) {
            iVar4 = m->neg;
          }
          rem->neg = iVar4;
          iVar4 = 1;
          dv->neg = m->neg ^ (recp->N).neg;
          goto LAB_002137bc;
        }
        iVar4 = iVar4 + -1;
      } while (((iVar4 != 0) && (iVar2 = BN_usub(rem,rem,&recp->N), iVar2 != 0)) &&
              (iVar2 = BN_add_word(dv,1), iVar2 != 0));
    }
  }
  iVar4 = 0;
LAB_002137bc:
  BN_CTX_end(ctx);
  return iVar4;
}

