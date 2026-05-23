// module: mt7915.ko
// function: APOneShotSettingInitialize @ 0x10574
// size: 192 bytes
//

undefined4 APOneShotSettingInitialize(int param_1)

{
  if (2 < DebugLevel) {
    printk("---> APOneShotSettingInitialize\n");
  }
  RTMPInitTimer(param_1,param_1 + 0x3687b0,rtmp_timer_CMTimerExec,param_1,0);
  MulticastFilterTableInit(param_1,param_1 + 0xa77bc4);
  RRM_CfgInit(param_1);
  AutoChBssTableInit(param_1);
  ChannelInfoInit(param_1);
  RTMP_11N_D3_TimerInit(param_1);
  QBSS_LoadInit(param_1);
  MATEngineInit(param_1);
  if (2 < DebugLevel) {
    printk("<--- APOneShotSettingInitialize\n");
  }
  return 0;
}

