// module: mt7915.ko
// function: RtmpOsSkbResetMacHeader @ 0x244e4c
// size: 20 bytes
//

void RtmpOsSkbResetMacHeader(int param_1)

{
  *(short *)(param_1 + 0xaa) =
       (short)*(undefined4 *)(param_1 + 0xcc) - (short)*(undefined4 *)(param_1 + 200);
  return;
}

