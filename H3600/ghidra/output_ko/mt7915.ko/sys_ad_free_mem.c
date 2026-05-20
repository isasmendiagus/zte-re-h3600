// module: mt7915.ko
// function: sys_ad_free_mem @ 0x25eab0
// size: 56 bytes
//

void sys_ad_free_mem(int param_1)

{
  if (param_1 != 0) {
    kfree(param_1);
    return;
  }
  printk(&_LC0,0x2d);
  dump_stack();
  kfree(0);
  return;
}

