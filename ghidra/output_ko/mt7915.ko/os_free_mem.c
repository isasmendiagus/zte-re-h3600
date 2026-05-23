// module: mt7915.ko
// function: os_free_mem @ 0x24574c
// size: 68 bytes
//

void os_free_mem(int param_1)

{
  if (param_1 == 0) {
    printk(&_LC48,0x1481);
    dump_stack();
  }
  kfree(param_1);
  g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + -1;
  return;
}

