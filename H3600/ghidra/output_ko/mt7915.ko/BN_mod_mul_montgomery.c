// module: mt7915.ko
// function: BN_mod_mul_montgomery @ 0x21368c
// size: 168 bytes
//

int BN_mod_mul_montgomery(BIGNUM *r,BIGNUM *a,BIGNUM *b,BN_MONT_CTX *mont,BN_CTX *ctx)

{
  BIGNUM *pBVar1;
  int iVar2;
  uint uVar3;
  
  BN_CTX_start(ctx);
  pBVar1 = BN_CTX_get(ctx);
  if (pBVar1 != (BIGNUM *)0x0) {
    if (a == b) {
      if (a != (BIGNUM *)0x0) {
        iVar2 = FUN_0020f4cc(pBVar1,a,ctx);
        goto joined_r0x0021372c;
      }
    }
    else if (b != (BIGNUM *)0x0 && a != (BIGNUM *)0x0) {
      iVar2 = FUN_00212078(pBVar1,a,b,ctx);
joined_r0x0021372c:
      if (iVar2 != 0) {
        iVar2 = FUN_0020e770(r,pBVar1,mont);
        uVar3 = (uint)(iVar2 != 0);
        goto LAB_002136d0;
      }
    }
  }
  uVar3 = 0;
LAB_002136d0:
  BN_CTX_end(ctx);
  return uVar3;
}

