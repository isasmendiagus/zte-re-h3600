// module: mt7915.ko
// function: sys_ad_move_mem @ 0x25eb08
// size: 4 bytes
//

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * sys_ad_move_mem(void *__dest,void *__src,size_t __n)

{
  void *pvVar1;
  
  pvVar1 = memmove(__dest,__src,__n);
  return pvVar1;
}

