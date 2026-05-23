// module: mt7915.ko
// function: RtmpDevPrivFlagsGet @ 0x2440bc
// size: 12 bytes
//

uint RtmpDevPrivFlagsGet(int param_1)

{
  return *(uint *)(param_1 + 0x4c8) & 0xffff;
}

