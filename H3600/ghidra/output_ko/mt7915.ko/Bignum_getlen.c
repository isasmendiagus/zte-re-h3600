// module: mt7915.ko
// function: Bignum_getlen @ 0x20c2cc
// size: 12 bytes
//

int Bignum_getlen(int param_1)

{
  return *(int *)(param_1 + 4) << 2;
}

