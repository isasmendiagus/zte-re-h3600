// module: mt7915.ko
// function: BN_POOL_finish @ 0x20eda0
// size: 100 bytes
//

void BN_POOL_finish(int *param_1)

{
  BIGNUM *pBVar1;
  BIGNUM *a;
  BIGNUM *pBVar2;
  
  pBVar1 = (BIGNUM *)*param_1;
  if (pBVar1 == (BIGNUM *)0x0) {
    return;
  }
  do {
    a = pBVar1;
    do {
      pBVar2 = a + 1;
      if (a->d != (ulong *)0x0) {
        BN_clear_free(a);
      }
      a = pBVar2;
    } while (pBVar2 != pBVar1 + 0x10);
    pBVar1 = *(BIGNUM **)(*param_1 + 0x144);
    param_1[1] = (int)pBVar1;
    if (*param_1 != 0) {
      os_free_mem();
      pBVar1 = (BIGNUM *)param_1[1];
    }
    *param_1 = (int)pBVar1;
  } while (pBVar1 != (BIGNUM *)0x0);
  return;
}

