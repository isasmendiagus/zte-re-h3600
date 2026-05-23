// module: mt7915.ko
// function: RtmpDevPrivFlagsSet @ 0x2440c8
// size: 8 bytes
//

void RtmpDevPrivFlagsSet(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x4c8) = param_2;
  return;
}

