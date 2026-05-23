// module: mt7915.ko
// function: sys_ad_init_os_task @ 0x25ecd4
// size: 128 bytes
//

undefined4 sys_ad_init_os_task(void *param_1,char *param_2,int param_3,int param_4)

{
  size_t __n;
  
  if (param_1 == (void *)0x0) {
    printk(&_LC5,0x86,param_3,param_4,param_4);
    dump_stack();
  }
  __n = strlen(param_2);
  if (0xe < (int)__n) {
    __n = 0xf;
  }
  os_move_mem(param_1,param_2,__n);
  if (param_3 != 0) {
    *(int *)((int)param_1 + 0x10) = param_3;
  }
  if (param_4 != 0) {
    *(int *)((int)param_1 + 0x14) = param_4;
  }
  __init_waitqueue_head((int)param_1 + 0x20,"&(task->kthread_q)",EEPROMValChange);
  return 0;
}

