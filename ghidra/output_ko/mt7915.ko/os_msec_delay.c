// module: mt7915.ko
// function: os_msec_delay @ 0x142a5c
// size: 4 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void os_msec_delay(int param_1)

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

