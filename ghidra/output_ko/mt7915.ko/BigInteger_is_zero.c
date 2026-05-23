// module: mt7915.ko
// function: BigInteger_is_zero @ 0x1fe1ac
// size: 80 bytes
//

bool BigInteger_is_zero(int param_1)

{
  BigInteger_ClearHighBits();
  if (param_1 == 0) {
    return false;
  }
  if ((*(int *)(param_1 + 0x18) == 1) && (*(int *)(param_1 + 0x1c) == 1)) {
    return **(int **)(param_1 + 0xc) == 0;
  }
  return false;
}

