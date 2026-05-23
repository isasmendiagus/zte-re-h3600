// module: mt7915.ko
// function: nonerp_protection @ 0x155ab4
// size: 28 bytes
//

bool nonerp_protection(int param_1)

{
  if (param_1 == 0) {
    return false;
  }
  return *(short *)(param_1 + 0x5064) != 0;
}

