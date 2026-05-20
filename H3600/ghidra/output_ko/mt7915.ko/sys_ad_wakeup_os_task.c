// module: mt7915.ko
// function: sys_ad_wakeup_os_task @ 0x25ed58
// size: 40 bytes
//

void sys_ad_wakeup_os_task(int param_1)

{
  if (*(int *)(param_1 + 0x1c) == 0) {
    return;
  }
  *(undefined1 *)(param_1 + 0x2c) = 1;
  __wake_up(param_1 + 0x20,3,1,0);
  return;
}

