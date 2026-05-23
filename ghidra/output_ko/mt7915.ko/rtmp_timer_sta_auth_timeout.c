// module: mt7915.ko
// function: rtmp_timer_sta_auth_timeout @ 0x76df0
// size: 56 bytes
//

void rtmp_timer_sta_auth_timeout(int param_1)

{
  sta_auth_timeout(0,*(undefined4 *)(param_1 + 0x24),0,param_1);
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

