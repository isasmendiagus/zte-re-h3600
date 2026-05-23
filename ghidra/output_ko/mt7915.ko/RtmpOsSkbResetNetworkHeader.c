// module: mt7915.ko
// function: RtmpOsSkbResetNetworkHeader @ 0x244e60
// size: 20 bytes
//

void RtmpOsSkbResetNetworkHeader(int param_1)

{
  *(short *)(param_1 + 0xa8) =
       (short)*(undefined4 *)(param_1 + 0xcc) - (short)*(undefined4 *)(param_1 + 200);
  return;
}

