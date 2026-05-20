// module: mt7915.ko
// function: RtmpOsNetPrivGet @ 0x142900
// size: 4 bytes
//

uint RtmpOsNetPrivGet(int param_1)

{
  return *(uint *)(param_1 + 0x4c8) & 0xffff;
}

