// module: mt7915.ko
// function: BN_get_word @ 0x20d830
// size: 44 bytes
//

ulong BN_get_word(BIGNUM *a)

{
  if (1 < a->top) {
    return 0xffffffff;
  }
  if (a->top != 1) {
    return 0;
  }
  return *a->d;
}

