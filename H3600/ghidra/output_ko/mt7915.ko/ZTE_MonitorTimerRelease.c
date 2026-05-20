// module: mt7915.ko
// function: ZTE_MonitorTimerRelease @ 0x159520
// size: 132 bytes
//

void ZTE_MonitorTimerRelease(int param_1,int param_2)

{
  uint uVar1;
  undefined1 auStack_11 [5];
  
  if (0 < DebugLevel) {
    printk("%s : band_idx value=%d\n","ZTE_MonitorTimerRelease",param_2);
  }
  if (param_2 == 0) {
    uVar1 = 0x76b0;
  }
  else {
    if (param_2 != 1) {
      return;
    }
    uVar1 = 0x76e4;
  }
  param_1 = param_1 + (uVar1 | 0xa30000);
  RTMPCancelTimer(param_1,auStack_11);
  RTMPReleaseTimer(param_1,auStack_11);
  return;
}

