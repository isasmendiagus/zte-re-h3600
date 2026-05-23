// module: mt7915.ko
// function: RTMPConstructWEPIVHdr @ 0x11837c
// size: 56 bytes
//

void RTMPConstructWEPIVHdr(char param_1,void *param_2,void *param_3)

{
  __memzero(param_3,4);
  memmove(param_3,param_2,3);
  *(char *)((int)param_3 + 3) = param_1 << 6;
  return;
}

