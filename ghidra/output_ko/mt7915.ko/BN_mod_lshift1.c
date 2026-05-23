// module: mt7915.ko
// function: BN_mod_lshift1 @ 0x211e48
// size: 80 bytes
//

int BN_mod_lshift1(BIGNUM *r,BIGNUM *a,BIGNUM *m,BN_CTX *ctx)

{
  int iVar1;
  
  if (a == (BIGNUM *)0x0 || r == (BIGNUM *)0x0) {
    return 0;
  }
  iVar1 = FUN_0020d528();
  if (iVar1 != 0) {
    iVar1 = BN_nnmod(r,r,m,ctx);
    return iVar1;
  }
  return 0;
}

