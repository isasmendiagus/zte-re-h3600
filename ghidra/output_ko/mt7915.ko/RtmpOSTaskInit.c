// module: mt7915.ko
// function: RtmpOSTaskInit @ 0x2455a0
// size: 108 bytes
//

undefined4 RtmpOSTaskInit(void *param_1,char *param_2,undefined4 param_3)

{
  size_t __n;
  
  if (param_1 == (void *)0x0) {
    printk(&_LC46,0x476);
    dump_stack();
  }
  __n = strlen(param_2);
  if (0xe < (int)__n) {
    __n = 0xf;
  }
  memmove(param_1,param_2,__n);
  *(undefined4 *)((int)param_1 + 0x10) = param_3;
  __init_waitqueue_head((int)param_1 + 0x20,"&(pTask->kthread_q)",&br0Addr);
  return 0;
}

