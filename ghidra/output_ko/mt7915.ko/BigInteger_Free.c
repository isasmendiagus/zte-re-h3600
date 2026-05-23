// module: mt7915.ko
// function: BigInteger_Free @ 0x1fb0f0
// size: 44 bytes
//

void BigInteger_Free(int *param_1)

{
  if (*param_1 != 0) {
    BigInteger_Free_AllocSize();
    os_free_mem(*param_1);
  }
  *param_1 = 0;
  return;
}

