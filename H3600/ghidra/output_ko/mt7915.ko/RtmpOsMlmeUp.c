// module: mt7915.ko
// function: RtmpOsMlmeUp @ 0x244b94
// size: 112 bytes
//

void RtmpOsMlmeUp(int param_1)

{
  if (param_1 == 0) {
    if (DebugLevel < 0) {
      return;
    }
  }
  else {
    if (*(int *)(param_1 + 0x1c) != 0) {
      *(undefined1 *)(param_1 + 0x2c) = 1;
      __wake_up(param_1 + 0x20,3,1,0);
      return;
    }
    if (DebugLevel < 0) {
      return;
    }
  }
  printk("%s invalid pTask 0x%p or kthread_task 0x%p\n","RtmpOsMlmeUp",param_1,0);
  return;
}

