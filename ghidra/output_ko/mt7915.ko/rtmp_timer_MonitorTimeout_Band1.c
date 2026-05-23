// module: mt7915.ko
// function: rtmp_timer_MonitorTimeout_Band1 @ 0x15613c
// size: 60 bytes
//

void rtmp_timer_MonitorTimeout_Band1(int param_1)

{
  queue_work_on(2,system_wq,&DAT_0034d508);
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

