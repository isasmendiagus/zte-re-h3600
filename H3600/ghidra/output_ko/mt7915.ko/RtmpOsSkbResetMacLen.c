// module: mt7915.ko
// function: RtmpOsSkbResetMacLen @ 0x244e88
// size: 20 bytes
//

void RtmpOsSkbResetMacLen(int param_1)

{
  *(short *)(param_1 + 0x6c) = *(short *)(param_1 + 0xa8) - *(short *)(param_1 + 0xaa);
  return;
}

