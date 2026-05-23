// module: mt7915.ko
// function: RTMPExtractKeyIdxFromIVHdr @ 0x118a64
// size: 32 bytes
//

byte RTMPExtractKeyIdxFromIVHdr(int param_1,undefined4 param_2)

{
  switch(param_2) {
  case 0:
  case 4:
  case 6:
  case 0xd:
  case 0xe:
    return *(byte *)(param_1 + 3) >> 6;
  default:
    return 0xff;
  }
}

