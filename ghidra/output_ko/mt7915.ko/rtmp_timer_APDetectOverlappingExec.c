// module: mt7915.ko
// function: rtmp_timer_APDetectOverlappingExec @ 0x140920
// size: 56 bytes
//

void rtmp_timer_APDetectOverlappingExec(int param_1)

{
  APDetectOverlappingExec(0,*(undefined4 *)(param_1 + 0x24),0,param_1);
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

