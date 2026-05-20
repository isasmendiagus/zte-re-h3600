// module: mt7915.ko
// function: RtmpOSFileSeek @ 0x243d80
// size: 16 bytes
//

void RtmpOSFileSeek(int param_1,int param_2)

{
  *(int *)(param_1 + 0x40) = param_2;
  *(int *)(param_1 + 0x44) = param_2 >> 0x1f;
  return;
}

