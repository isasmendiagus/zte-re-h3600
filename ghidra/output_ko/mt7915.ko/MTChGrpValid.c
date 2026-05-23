// module: mt7915.ko
// function: MTChGrpValid @ 0x141638
// size: 40 bytes
//

bool MTChGrpValid(int param_1)

{
  if (*(byte *)(param_1 + 0x4d9) - 1 < 0x3a) {
    return *(char *)(param_1 + 0x49d) != '\0';
  }
  return false;
}

