// module: mt7915.ko
// function: rtmp_timer_sta_assoc_timeout @ 0x80274
// size: 168 bytes
//

void rtmp_timer_sta_assoc_timeout(int param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 + 0x24);
  iVar1 = *piVar2;
  if (0 < DebugLevel) {
    printk("ASSOC - enqueue ASSOC_FSM_ASSOC_TIMEOUT\n");
  }
  if ((*(uint *)(iVar1 + 0xa39f84) & 0x140) == 0) {
    MlmeEnqueueWithWdev(iVar1,1,9,0,0,0,piVar2[1]);
    RtmpOsMlmeUp(iVar1 + 0x286298);
  }
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

