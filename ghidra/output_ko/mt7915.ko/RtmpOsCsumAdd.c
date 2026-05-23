// module: mt7915.ko
// function: RtmpOsCsumAdd @ 0x244db4
// size: 20 bytes
//

int RtmpOsCsumAdd(uint param_1,uint param_2)

{
  return (uint)CARRY4(param_1,param_2) + param_1 + param_2;
}

