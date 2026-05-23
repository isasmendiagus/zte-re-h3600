// module: tm.ko
// function: pm_set_flow_sta_read_clear_en @ 0x3407c
// size: 180 bytes
//

undefined4
pm_set_flow_sta_read_clear_en(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (g_tm_debug_level < 7) {
    if (param_1 < 2) {
LAB_000340a8:
      iVar1 = tmOnuRegWrite(10,param_1,0,pmRegTable);
      if (iVar1 == 0) {
        return 0;
      }
      if ((g_tm_debug_level != 0) &&
         (iVar1 = ___ratelimit(_rs_7280,"pm_set_flow_sta_read_clear_en"), iVar1 != 0)) {
        printk("[TM][pm_set_flow_sta_read_clear_en]reg write failed\n");
      }
      return 0xffffffff;
    }
  }
  else {
    printk("[TM][pm_set_flow_sta_read_clear_en]input: read_clear_en = %d\n",param_1,param_3,
           g_tm_debug_level,param_4);
    if (param_1 < 2) goto LAB_000340a8;
    if (6 < g_tm_debug_level) {
      printk("[TM][pm_set_flow_sta_read_clear_en]input invalid parameter!\n");
    }
  }
  return 1;
}

