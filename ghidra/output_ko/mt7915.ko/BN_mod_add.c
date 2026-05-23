// module: mt7915.ko
// function: BN_mod_add @ 0x211de0
// size: 52 bytes
//

int BN_mod_add(BIGNUM *r,BIGNUM *a,BIGNUM *b,BIGNUM *m,BN_CTX *ctx)

{
  int iVar1;
  
  iVar1 = BN_add(r,a,b);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = BN_nnmod(r,r,m,ctx);
  return iVar1;
}

