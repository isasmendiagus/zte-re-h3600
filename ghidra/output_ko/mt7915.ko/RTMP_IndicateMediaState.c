// module: mt7915.ko
// function: RTMP_IndicateMediaState @ 0x14fb38
// size: 16 bytes
//

void RTMP_IndicateMediaState(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x794ae4) = param_2;
  return;
}

