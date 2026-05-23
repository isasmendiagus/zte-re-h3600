// module: mt7915.ko
// function: rtmp_ap_exit @ 0x16ae4
// size: 80 bytes
//

void rtmp_ap_exit(int param_1)

{
  undefined1 uStack_9;
  
  RTMPReleaseTimer(param_1 + 0x3687b0,&uStack_9);
  RTMP_11N_D3_TimerRelease(param_1);
  AutoChBssTableDestroy(param_1);
  ChannelInfoDestroy(param_1);
  MultiCastFilterTableReset(param_1,param_1 + 0xa77bc4);
  return;
}

