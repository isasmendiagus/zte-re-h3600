// module: mt7915.ko
// function: RtmpPktPmBitCheck @ 0x1dd774
// size: 32 bytes
//

bool RtmpPktPmBitCheck(undefined4 param_1,int param_2)

{
  return *(short *)(param_2 + 0x2124b8) == 1;
}

