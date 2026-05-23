// module: mt7915.ko
// function: BN_mod_mul_reciprocal @ 0x2139a4
// size: 188 bytes
//

int BN_mod_mul_reciprocal(BIGNUM *r,BIGNUM *x,BIGNUM *y,BN_RECP_CTX *recp,BN_CTX *ctx)

{
  BIGNUM *pBVar1;
  int iVar2;
  
  BN_CTX_start(ctx);
  pBVar1 = BN_CTX_get(ctx);
  if (pBVar1 == (BIGNUM *)0x0) {
LAB_002139ec:
    iVar2 = 0;
  }
  else {
    if (y != (BIGNUM *)0x0) {
      if (x == y) {
        iVar2 = FUN_0020f4cc(pBVar1,x,ctx);
      }
      else {
        if (x == (BIGNUM *)0x0) goto LAB_002139ec;
        iVar2 = FUN_00212078(pBVar1,x,y,ctx);
      }
      x = pBVar1;
      if (iVar2 == 0) goto LAB_002139ec;
    }
    iVar2 = BN_div_recp((BIGNUM *)0x0,r,x,recp,ctx);
  }
  BN_CTX_end(ctx);
  return iVar2;
}

