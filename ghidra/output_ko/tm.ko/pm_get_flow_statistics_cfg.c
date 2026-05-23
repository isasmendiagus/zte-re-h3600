// module: tm.ko
// function: pm_get_flow_statistics_cfg @ 0x354b8
// size: 220 bytes
//

undefined4 pm_get_flow_statistics_cfg(uint param_1,uint *param_2)

{
  int iVar1;
  uint local_10;
  uint local_c;
  
  local_10 = 0;
  local_c = 0;
  if (0x3ff < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][pm_get_flow_statistics_cfg]input invalid parameter!\n");
    }
    return 1;
  }
  iVar1 = pm_get_indirect_data(4,param_1,&local_10);
  if (iVar1 != 0) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7459,"pm_get_flow_statistics_cfg"), iVar1 != 0)) {
      printk("[TM][pm_get_zte_statistics_cfg]indirect access failed\n");
    }
    return 0xffffffff;
  }
  *param_2 = local_10 & 0x1fffffff;
  param_2[2] = local_c << 3 | local_10 >> 0x1d;
  param_2[3] = local_c >> 0x1d;
  return 0;
}

