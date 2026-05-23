// module: mt7915.ko
// function: sys_ad_kill_os_task @ 0x25ebd8
// size: 104 bytes
//

undefined4 sys_ad_kill_os_task(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x1c) == 0) {
    printk("%s null kthread_task %s\n","_sys_ad_kill_os_task",param_1);
    return 0x700;
  }
  iVar1 = kthread_stop();
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x1c) = 0;
    return 0;
  }
  printk("%s kthread_task %s stop failed\n","_sys_ad_kill_os_task",param_1);
  return 0x700;
}

