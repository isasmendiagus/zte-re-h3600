// module: mt7915.ko
// function: BigInteger_is_one @ 0x1fe1fc
// size: 84 bytes
//

bool BigInteger_is_one(int param_1)

{
  BigInteger_ClearHighBits();
  if (param_1 == 0) {
    return false;
  }
  if ((*(int *)(param_1 + 0x18) == 1) && (*(int *)(param_1 + 0x1c) == 1)) {
    return **(int **)(param_1 + 0xc) == 1;
  }
  return false;
}

