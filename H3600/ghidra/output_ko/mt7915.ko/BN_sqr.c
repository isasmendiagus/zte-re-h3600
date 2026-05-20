// module: mt7915.ko
// function: BN_sqr @ 0x2108c0
// size: 24 bytes
//

int BN_sqr(BIGNUM *r,BIGNUM *a,BN_CTX *ctx)

{
  int iVar1;
  
  if (a != (BIGNUM *)0x0 && r != (BIGNUM *)0x0) {
    iVar1 = FUN_0020f4cc();
    return iVar1;
  }
  return 0;
}

