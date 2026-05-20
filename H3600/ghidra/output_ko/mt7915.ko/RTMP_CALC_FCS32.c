// module: mt7915.ko
// function: RTMP_CALC_FCS32 @ 0x11828c
// size: 52 bytes
//

void RTMP_CALC_FCS32(undefined4 param_1,int param_2,int param_3)

{
  if (param_3 == 0) {
    return;
  }
  param_3 = param_2 + param_3;
  do {
    param_2 = param_2 + 1;
  } while (param_2 != param_3);
  return;
}

