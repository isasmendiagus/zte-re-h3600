// module: mt7915.ko
// function: RtmpOsSkbResetTransportHeader @ 0x244e74
// size: 20 bytes
//

void RtmpOsSkbResetTransportHeader(int param_1)

{
  *(short *)(param_1 + 0xa6) =
       (short)*(undefined4 *)(param_1 + 0xcc) - (short)*(undefined4 *)(param_1 + 200);
  return;
}

