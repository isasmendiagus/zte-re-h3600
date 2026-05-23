// module: mt7915.ko
// function: rtmp_timer_restart_partial_scan @ 0x142a64
// size: 32 bytes
//

void rtmp_timer_restart_partial_scan(int param_1)

{
  **(undefined1 **)(param_1 + 0x24) = 1;
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

