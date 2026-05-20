// module: mt7915.ko
// function: BN_CTX_get @ 0x20f0f8
// size: 116 bytes
//

BIGNUM * BN_CTX_get(BN_CTX *ctx)

{
  BIGNUM *pBVar1;
  
  if (ctx == (BN_CTX *)0x0) {
    return (BIGNUM *)0x0;
  }
  if (*(int *)(ctx + 0x24) != 0) {
    return (BIGNUM *)0x0;
  }
  if (*(int *)(ctx + 0x28) != 0) {
    return (BIGNUM *)0x0;
  }
  pBVar1 = (BIGNUM *)BN_POOL_get(ctx,*(undefined4 *)(ctx + 0x2c));
  if (pBVar1 == (BIGNUM *)0x0) {
    *(undefined4 *)(ctx + 0x28) = 1;
  }
  else {
    pBVar1->top = 0;
    pBVar1->neg = 0;
    *(int *)(ctx + 0x20) = *(int *)(ctx + 0x20) + 1;
  }
  return pBVar1;
}

