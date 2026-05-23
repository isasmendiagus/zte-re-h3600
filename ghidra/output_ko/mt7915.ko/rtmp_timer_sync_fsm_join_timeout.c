// module: mt7915.ko
// function: rtmp_timer_sync_fsm_join_timeout @ 0x10b878
// size: 172 bytes
//

void rtmp_timer_sync_fsm_join_timeout(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  piVar1 = *(int **)(param_1 + 0x24);
  iVar2 = *piVar1;
  iVar3 = piVar1[1];
  if (2 < DebugLevel) {
    printk("%s - Enter\n","sync_fsm_join_timeout");
  }
  if ((*(uint *)(iVar2 + 0xa39f84) & 0x40) == 0) {
    MlmeEnqueueWithWdev(iVar2,4,1,0,0,*(undefined1 *)(iVar3 + 0xe),piVar1[1]);
    RtmpOsMlmeUp(iVar2 + 0x286298);
  }
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

