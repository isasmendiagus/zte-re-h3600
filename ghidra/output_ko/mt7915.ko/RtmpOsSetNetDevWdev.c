// module: mt7915.ko
// function: RtmpOsSetNetDevWdev @ 0x2440ac
// size: 8 bytes
//

void RtmpOsSetNetDevWdev(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x4c4) = param_2;
  return;
}

