// module: mt7915.ko
// function: RTMP_11N_D3_TimerRelease @ 0x13cc44
// size: 36 bytes
//

void RTMP_11N_D3_TimerRelease(int param_1)

{
  undefined1 auStack_9 [5];
  
  RTMPReleaseTimer(param_1 + 0x795654,auStack_9);
  return;
}

