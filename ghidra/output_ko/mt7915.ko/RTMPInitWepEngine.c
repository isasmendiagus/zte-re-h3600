// module: mt7915.ko
// function: RTMPInitWepEngine @ 0x1182c0
// size: 188 bytes
//

void RTMPInitWepEngine(void *param_1,void *param_2,size_t param_3,undefined4 param_4)

{
  void *local_1c [2];
  
  local_1c[0] = (void *)0x0;
  os_alloc_mem(0,local_1c,0x10);
  if (local_1c[0] == (void *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: seed Allocate memory fail!!!\n","RTMPInitWepEngine");
    }
  }
  else {
    __memzero(local_1c[0],0x10);
    memmove(local_1c[0],param_1,3);
    memmove((void *)((int)local_1c[0] + 3),param_2,param_3);
    ARC4_INIT(param_4,local_1c[0],param_3 + 3 & 0xff);
    os_free_mem(local_1c[0]);
  }
  return;
}

