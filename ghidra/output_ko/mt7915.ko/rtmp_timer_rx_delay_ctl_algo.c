// module: mt7915.ko
// function: rtmp_timer_rx_delay_ctl_algo @ 0xcde00
// size: 20 bytes
//

void rtmp_timer_rx_delay_ctl_algo(int param_1)

{
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

