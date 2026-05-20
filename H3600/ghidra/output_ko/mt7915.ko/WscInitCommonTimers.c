// module: mt7915.ko
// function: WscInitCommonTimers @ 0x1e0b74
// size: 252 bytes
//

void WscInitCommonTimers(undefined4 param_1,int param_2)

{
  RTMPInitTimer(param_1,param_2 + 0x27cc,rtmp_timer_WscEAPOLTimeOutAction,param_2,0);
  *(undefined1 *)(param_2 + 0x27c8) = 0;
  RTMPInitTimer(param_1,param_2 + 0x1c5c,rtmp_timer_Wsc2MinsTimeOutAction,param_2,0);
  *(undefined1 *)(param_2 + 0x1c5b) = 0;
  RTMPInitTimer(param_1,param_2 + 0x2794,rtmp_timer_WscUPnPMsgTimeOutAction,param_2,0);
  *(undefined1 *)(param_2 + 0x278d) = 0;
  *(undefined1 *)(param_2 + 0x278e) = 0;
  RTMPInitTimer(param_1,param_2 + 0x2c10,rtmp_timer_WscM2DTimeOutAction,param_2,0);
  *(undefined1 *)(param_2 + 0x2c44) = 0;
  RTMPInitTimer(param_1,param_2 + 0x2930,rtmp_timer_WscLEDTimer,param_2,0);
  *(undefined1 *)(param_2 + 0x292d) = 0;
  RTMPInitTimer(param_1,param_2 + 0x2968,rtmp_timer_WscSkipTurnOffLEDTimer,param_2,0);
  *(undefined1 *)(param_2 + 0x2964) = 0;
  return;
}

