// module: mt7915.ko
// function: ZTE_MonitorTimerInit @ 0x15946c
// size: 176 bytes
//

void ZTE_MonitorTimerInit(int param_1,int param_2)

{
  if (0 < DebugLevel) {
    printk("%s : band_idx value=%d\n","ZTE_MonitorTimerInit",param_2);
  }
  if (param_2 != 0) {
    if (param_2 != 1) {
      return;
    }
    RTMPInitTimer(param_1,param_1 + 0xa376e4,rtmp_timer_MonitorTimeout_Band1,param_1,0);
    return;
  }
  RTMPInitTimer(param_1,param_1 + 0xa376b0,rtmp_timer_MonitorTimeout_Band0,param_1,0);
  return;
}

