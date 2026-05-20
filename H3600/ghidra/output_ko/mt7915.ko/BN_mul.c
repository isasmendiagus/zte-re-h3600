// module: mt7915.ko
// function: BN_mul @ 0x216330
// size: 24 bytes
//

int BN_mul(BIGNUM *r,BIGNUM *a,BIGNUM *b,BN_CTX *ctx)

{
  int iVar1;
  
  if (b != (BIGNUM *)0x0 && a != (BIGNUM *)0x0) {
    iVar1 = FUN_00212078();
    return iVar1;
  }
  return 0;
}

