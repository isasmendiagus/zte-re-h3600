// module: tm.ko
// function: sadm_set_bucket_fill_time @ 0x244d8
// size: 216 bytes
//

undefined4
sadm_set_bucket_fill_time(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  if (0x40000 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_14414,"sadm_set_bucket_fill_time"), iVar1 != 0)) {
      printk("[TM][sadm_set_bucket_fill_time]input invalid parameter!\n");
    }
    return 1;
  }
  uVar2 = param_1;
  if (param_1 < 0x1ff) {
    uVar2 = 0x1ff;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_set_bucket_fill_time]input:time = %d\n",param_1,0x1ff,g_tm_debug_level,param_4
          );
  }
  iVar1 = tmOnuRegWrite(0xc,uVar2,0,sadmRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_14417,"sadm_set_bucket_fill_time"), iVar1 != 0)) {
    printk("[TM][sadm_set_bucket_fill_time]write reg failed!\n");
  }
  return 0xffffffff;
}

