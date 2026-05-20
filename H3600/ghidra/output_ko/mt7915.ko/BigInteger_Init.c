// module: mt7915.ko
// function: BigInteger_Init @ 0x1fb0d0
// size: 32 bytes
//

void BigInteger_Init(int *param_1)

{
  if (*param_1 == 0) {
    FUN_001fae18();
    return;
  }
  if (*(char *)(*param_1 + 0x20) != '\0') {
    return;
  }
  BigInteger_Free_AllocSize();
  return;
}

