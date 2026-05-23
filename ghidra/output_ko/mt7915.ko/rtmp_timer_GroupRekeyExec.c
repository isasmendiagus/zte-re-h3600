// module: mt7915.ko
// function: rtmp_timer_GroupRekeyExec @ 0x188e0
// size: 56 bytes
//

void rtmp_timer_GroupRekeyExec(int param_1)

{
  GroupRekeyExec(0,*(undefined4 *)(param_1 + 0x24),0,param_1);
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

