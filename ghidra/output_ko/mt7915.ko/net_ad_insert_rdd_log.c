// module: mt7915.ko
// function: net_ad_insert_rdd_log @ 0x25ac1c
// size: 124 bytes
//

undefined4 net_ad_insert_rdd_log(undefined4 *param_1,void *param_2,uint param_3,undefined4 param_4)

{
  uint extraout_r2;
  uint __n;
  
  if (param_2 != (void *)0x0 && param_1 != (undefined4 *)0x0) {
    sys_ad_zero_mem(param_1,0x1c);
    __n = extraout_r2;
    if (param_3 < 0x14) {
      __n = param_3;
    }
    *param_1 = 4;
    if (param_3 >= 0x14) {
      __n = 0x14;
    }
    *(undefined1 *)(param_1 + 1) = 1;
    sys_ad_move_mem(param_1 + 2,param_2,__n);
    return 0;
  }
  printk("%s: NULL entry %p, data %p\n","net_ad_insert_rdd_log",param_1,param_2,param_4);
  return 0x606;
}

