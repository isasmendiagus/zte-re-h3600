// module: mt7915.ko
// function: isMemberOnMWDSLink @ 0x241f94
// size: 16 bytes
//

bool isMemberOnMWDSLink(int param_1)

{
  return *(char *)(param_1 + 10) != '\0';
}

