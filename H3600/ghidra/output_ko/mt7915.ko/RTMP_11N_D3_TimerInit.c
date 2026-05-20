// module: mt7915.ko
// function: RTMP_11N_D3_TimerInit @ 0x13cc10
// size: 52 bytes
//

void RTMP_11N_D3_TimerInit(int param_1)

{
  RTMPInitTimer(param_1,param_1 + 0x795654,rtmp_timer_Bss2040CoexistTimeOut,param_1,0);
  return;
}

