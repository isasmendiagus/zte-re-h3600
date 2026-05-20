// module: mt7915.ko
// function: rtmp_timer_MonitorTimeout_Band0 @ 0x1560fc
// size: 64 bytes
//

void rtmp_timer_MonitorTimeout_Band0(int param_1)

{
  queue_work_on(2,system_wq,&_LANCHOR1);
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

