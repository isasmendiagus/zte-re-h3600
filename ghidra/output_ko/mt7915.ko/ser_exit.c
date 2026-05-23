// module: mt7915.ko
// function: ser_exit @ 0xb23b0
// size: 16 bytes
//

void ser_exit(int param_1)

{
  RtmpOSTaskKill(param_1 + 0x285cfc);
  return;
}

