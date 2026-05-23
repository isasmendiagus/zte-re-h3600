// module: mt7915.ko
// function: RtmpOSTaskKill @ 0x2453fc
// size: 140 bytes
//

undefined4 RtmpOSTaskKill(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x1c) == 0) {
    if (1 < DebugLevel) {
      printk("%s null kthread_task %s\n","__RtmpOSTaskKill",param_1);
    }
  }
  else {
    iVar1 = kthread_stop();
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0x1c) = 0;
      return 0;
    }
    if (1 < DebugLevel) {
      printk("%s kthread_task %s stop failed\n","__RtmpOSTaskKill",param_1);
      return 1;
    }
  }
  return 1;
}

