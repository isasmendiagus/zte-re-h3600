// module: mt7915.ko
// function: RtmpOsCmdUp @ 0x244b78
// size: 28 bytes
//

void RtmpOsCmdUp(int param_1)

{
  *(undefined1 *)(param_1 + 0x2c) = 1;
  __wake_up(param_1 + 0x20,3,1,0);
  return;
}

