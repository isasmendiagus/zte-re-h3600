// module: mt7915.ko
// function: RtmpOsCmdDisplayLenCheck @ 0x142904
// size: 24 bytes
//

bool RtmpOsCmdDisplayLenCheck(uint param_1,int param_2)

{
  return param_1 <= 0x7ffU - param_2;
}

