// module: tm.ko
// function: pm_set_flow_sta_cnt_mode @ 0x3413c
// size: 180 bytes
//

undefined4
pm_set_flow_sta_cnt_mode(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (g_tm_debug_level < 7) {
    if (param_1 < 2) {
LAB_00034168:
      iVar1 = tmOnuRegWrite(0xb,param_1,0,pmRegTable);
      if (iVar1 == 0) {
        return 0;
      }
      if ((g_tm_debug_level != 0) &&
         (iVar1 = ___ratelimit(_rs_7287,"pm_set_flow_sta_cnt_mode"), iVar1 != 0)) {
        printk("[TM][pm_set_flow_sta_cnt_mode]reg write failed\n");
      }
      return 0xffffffff;
    }
  }
  else {
    printk("[TM][pm_set_flow_sta_cnt_mode]input: mode = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
    if (param_1 < 2) goto LAB_00034168;
    if (6 < g_tm_debug_level) {
      printk("[TM][pm_set_flow_sta_cnt_mode]input invalid parameter!\n");
    }
  }
  return 1;
}

