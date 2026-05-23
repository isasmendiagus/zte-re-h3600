// module: mt7915.ko
// function: SetCommonVHT @ 0x201c98
// size: 44 bytes
//

ushort SetCommonVHT(undefined4 param_1,int param_2)

{
  if ((*(ushort *)(param_2 + 0x18) & 0x20) == 0) {
    return *(ushort *)(param_2 + 0x18) & 0x20;
  }
  RTMPSetVHT();
  return 1;
}

