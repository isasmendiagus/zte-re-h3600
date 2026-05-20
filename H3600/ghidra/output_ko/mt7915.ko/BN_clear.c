// module: mt7915.ko
// function: BN_clear @ 0x20d7fc
// size: 52 bytes
//

void BN_clear(BIGNUM *a)

{
  if ((a->d != (ulong *)0x0) && ((a->dmax & 0x3fffffffU) != 0)) {
    __memzero();
  }
  a->top = 0;
  a->neg = 0;
  return;
}

