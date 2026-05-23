// module: mt7915.ko
// function: MT_ATEInsertRDD @ 0x27f840
// size: 152 bytes
//

undefined4 MT_ATEInsertRDD(undefined4 *param_1,void *param_2,uint param_3,undefined4 param_4)

{
  uint extraout_r2;
  uint __n;
  
  if (param_2 != (void *)0x0 && param_1 != (undefined4 *)0x0) {
    os_zero_mem(param_1,0x2c);
    __n = extraout_r2;
    if (param_3 < 0x14) {
      __n = param_3;
    }
    *param_1 = 4;
    if (param_3 >= 0x14) {
      __n = 0x14;
    }
    *(undefined1 *)(param_1 + 1) = 1;
    memmove(param_1 + 2,param_2,__n);
    return 0;
  }
  if (-1 < DebugLevel) {
    printk("%s: NULL entry %p, data %p\n","MT_ATEInsertRDD",param_1,param_2,param_4);
    return 0xffffffff;
  }
  return 0xffffffff;
}

