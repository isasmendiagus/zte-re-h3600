// module: tm.ko
// function: sadm_set_bucket_overspeed_threshold @ 0x23f3c
// size: 204 bytes
//

undefined4
sadm_set_bucket_overspeed_threshold
          (uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0x1fffff < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_14355,"sadm_set_bucket_overspeed_threshold"), iVar1 != 0)) {
      printk("[TM][sadm_set_bucket_overspeed_threshold]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_set_bucket_overspeed_threshold]input:threshold = %d\n",param_1,param_3,
           g_tm_debug_level,param_4);
  }
  iVar1 = tmOnuRegWrite(9,param_1,0,sadmRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_14358,"sadm_set_bucket_overspeed_threshold"), iVar1 != 0)) {
    printk("[TM][sadm_set_bucket_overspeed_threshold]write reg failed!\n");
  }
  return 0xffffffff;
}

