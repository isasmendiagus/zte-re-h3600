// module: mt7915.ko
// function: RtmpOsMsDelay @ 0x243274
// size: 52 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void RtmpOsMsDelay(int param_1)

{
  if (param_1 != 0) {
    do {
      (*_memcpy)(0x66665b0);
      param_1 = param_1 + -1;
    } while (param_1 != 0);
    return;
  }
  return;
}

