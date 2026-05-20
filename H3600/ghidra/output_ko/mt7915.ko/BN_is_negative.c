// module: mt7915.ko
// function: BN_is_negative @ 0x20e11c
// size: 24 bytes
//

bool BN_is_negative(int param_1)

{
  if (param_1 == 0) {
    return false;
  }
  return *(int *)(param_1 + 0xc) != 0;
}

