// module: mt7915.ko
// function: RTMP_SetPeriodicTimer @ 0x2452d8
// size: 68 bytes
//

void RTMP_SetPeriodicTimer(int *param_1,int param_2)

{
  if (*param_1 != 0) {
    return;
  }
  param_1[2] = jiffies + (uint)(param_2 * 100) / 1000;
  add_timer(param_1,param_2 * 100,param_2 * 0x6666666c);
  return;
}

