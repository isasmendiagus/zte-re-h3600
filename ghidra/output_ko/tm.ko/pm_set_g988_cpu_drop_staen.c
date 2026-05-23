// module: tm.ko
// function: pm_set_g988_cpu_drop_staen @ 0x3383c
// size: 180 bytes
//

undefined4
pm_set_g988_cpu_drop_staen(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (g_tm_debug_level < 7) {
    if (param_1 < 2) {
LAB_00033868:
      iVar1 = tmOnuRegWrite(4,param_1,0,pmRegTable);
      if (iVar1 == 0) {
        return 0;
      }
      if ((g_tm_debug_level != 0) &&
         (iVar1 = ___ratelimit(_rs_7191,"pm_set_g988_cpu_drop_staen"), iVar1 != 0)) {
        printk("[TM][pm_set_g988_cpu_drop_staen]reg write failed\n");
      }
      return 0xffffffff;
    }
  }
  else {
    printk("[TM][pm_set_g988_cpu_drop_staen]input: sta_en = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
    if (param_1 < 2) goto LAB_00033868;
    if (6 < g_tm_debug_level) {
      printk("[TM][pm_set_g988_cpu_drop_staen]input invalid parameter!\n");
    }
  }
  return 1;
}

