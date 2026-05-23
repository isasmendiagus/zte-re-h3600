// module: mt7915.ko
// function: RTMP_OS_Init_Timer @ 0x24531c
// size: 60 bytes
//

void RTMP_OS_Init_Timer(undefined4 param_1,int *param_2,int param_3,int param_4)

{
  if (*param_2 != 0) {
    return;
  }
  init_timer_key(param_2,0,0,0);
  param_2[5] = param_4;
  param_2[4] = param_3;
  return;
}

