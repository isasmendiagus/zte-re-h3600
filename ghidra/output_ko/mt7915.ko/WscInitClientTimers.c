// module: mt7915.ko
// function: WscInitClientTimers @ 0x1e0c70
// size: 204 bytes
//

void WscInitClientTimers(undefined4 param_1,int param_2)

{
  RTMPInitTimer(param_1,param_2 + 0x2808,rtmp_timer_WscPBCTimeOutAction,param_2,0);
  *(undefined1 *)(param_2 + 0x2804) = 0;
  RTMPInitTimer(param_1,param_2 + 0x28ec,rtmp_timer_WscPINTimeOutAction,param_2,0);
  *(undefined1 *)(param_2 + 0x28e8) = 0;
  RTMPInitTimer(param_1,param_2 + 0x2840,rtmp_timer_WscScanTimeOutAction,param_2,0);
  *(undefined1 *)(param_2 + 0x283c) = 0;
  RTMPInitTimer(param_1,param_2 + 0x2878,rtmp_timer_WscProfileRetryTimeout,param_2,0);
  *(undefined1 *)(param_2 + 0x2874) = 0;
  RTMPInitTimer(param_1,param_2 + 0x28b0,rtmp_timer_WscScanDoneCheckTimeOutAction,param_2,0);
  *(undefined1 *)(param_2 + 0x28ac) = 0;
  return;
}

