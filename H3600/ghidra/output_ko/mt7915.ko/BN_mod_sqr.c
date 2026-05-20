// module: mt7915.ko
// function: BN_mod_sqr @ 0x211f1c
// size: 100 bytes
//

int BN_mod_sqr(BIGNUM *r,BIGNUM *a,BIGNUM *m,BN_CTX *ctx)

{
  int iVar1;
  
  if ((a != (BIGNUM *)0x0 && r != (BIGNUM *)0x0) && (iVar1 = FUN_0020f4cc(r,a,ctx), iVar1 != 0)) {
    iVar1 = BN_div((BIGNUM *)0x0,r,r,m,ctx);
    return iVar1;
  }
  return 0;
}

