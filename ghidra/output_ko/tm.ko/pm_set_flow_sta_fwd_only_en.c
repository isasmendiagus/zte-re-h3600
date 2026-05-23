// module: tm.ko
// function: pm_set_flow_sta_fwd_only_en @ 0x341fc
// size: 180 bytes
//

undefined4
pm_set_flow_sta_fwd_only_en(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (g_tm_debug_level < 7) {
    if (param_1 < 2) {
LAB_00034228:
      iVar1 = tmOnuRegWrite(0xc,param_1,0,pmRegTable);
      if (iVar1 == 0) {
        return 0;
      }
      if ((g_tm_debug_level != 0) &&
         (iVar1 = ___ratelimit(_rs_7294,"pm_set_flow_sta_fwd_only_en"), iVar1 != 0)) {
        printk("[TM][pm_set_flow_sta_fwd_only_en]reg write failed\n");
      }
      return 0xffffffff;
    }
  }
  else {
    printk("[TM][pm_set_flow_sta_fwd_only_en]input: fwd_only_en = %d\n",param_1,param_3,
           g_tm_debug_level,param_4);
    if (param_1 < 2) goto LAB_00034228;
    if (6 < g_tm_debug_level) {
      printk("[TM][pm_set_flow_sta_fwd_only_en]input invalid parameter!\n");
    }
  }
  return 1;
}

