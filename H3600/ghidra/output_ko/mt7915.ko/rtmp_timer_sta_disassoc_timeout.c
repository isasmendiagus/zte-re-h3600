// module: mt7915.ko
// function: rtmp_timer_sta_disassoc_timeout @ 0x8016c
// size: 132 bytes
//

void rtmp_timer_sta_disassoc_timeout(int param_1)

{
  int iVar1;
  
  iVar1 = **(int **)(param_1 + 0x24);
  if ((*(uint *)(iVar1 + 0xa39f84) & 0x140) == 0) {
    MlmeEnqueueWithWdev(iVar1,1,8,0,0,0,(*(int **)(param_1 + 0x24))[1]);
    RtmpOsMlmeUp(iVar1 + 0x286298);
  }
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

