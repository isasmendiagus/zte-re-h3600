// module: mt7915.ko
// function: BN_set_negative @ 0x20db48
// size: 52 bytes
//

void BN_set_negative(BIGNUM *b,int n)

{
  if ((n != 0) && ((b == (BIGNUM *)0x0 || (b->top != 0)))) {
    b->neg = 1;
    return;
  }
  b->neg = 0;
  return;
}

