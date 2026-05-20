// module: mt7915.ko
// function: MT_ATEInsertReCal @ 0x27f7b0
// size: 140 bytes
//

undefined4 MT_ATEInsertReCal(undefined4 *param_1,void *param_2)

{
  if (param_2 != (void *)0x0 && param_1 != (undefined4 *)0x0) {
    os_zero_mem(param_1,0x2c);
    *param_1 = 8;
    *(undefined1 *)(param_1 + 1) = 1;
    memmove(param_1 + 2,param_2,0x10);
    return 0;
  }
  if (-1 < DebugLevel) {
    printk("%s: NULL entry %p, data %p\n","MT_ATEInsertReCal",param_1,param_2);
    return 1;
  }
  return 1;
}

