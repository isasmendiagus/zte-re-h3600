// module: tm.ko
// function: sadm_set_pps_type @ 0x23478
// size: 204 bytes
//

undefined4 sadm_set_pps_type(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (7 < param_1) {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_14240,"sadm_set_pps_type"), iVar1 != 0)
       ) {
      printk("[TM][sadm_set_pps_type]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_set_pps_type]input:mask = 0x%x\n",param_1,param_3,g_tm_debug_level,param_4);
  }
  iVar1 = tmOnuRegWrite(2,param_1,0,sadmRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_14243,"sadm_set_pps_type"), iVar1 != 0))
  {
    printk("[TM][sadm_set_pps_type]write reg failed!\n");
  }
  return 0xffffffff;
}

