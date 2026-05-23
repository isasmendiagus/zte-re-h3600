// module: tm.ko
// function: pm_set_g988_inport_equal_outport_staen @ 0x339bc
// size: 180 bytes
//

undefined4
pm_set_g988_inport_equal_outport_staen
          (uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (g_tm_debug_level < 7) {
    if (param_1 < 3) {
LAB_000339e8:
      iVar1 = tmOnuRegWrite(0x10,param_1,0,pmRegTable);
      if (iVar1 == 0) {
        return 0;
      }
      if ((g_tm_debug_level != 0) &&
         (iVar1 = ___ratelimit(_rs_7205,"pm_set_g988_inport_equal_outport_staen"), iVar1 != 0)) {
        printk("[TM][pm_set_g988_inport_equal_outport_staen]reg write failed\n");
      }
      return 0xffffffff;
    }
  }
  else {
    printk("[TM][pm_set_g988_inport_equal_outport_staen]input: stamode = %d\n",param_1,param_3,
           g_tm_debug_level,param_4);
    if (param_1 < 3) goto LAB_000339e8;
    if (6 < g_tm_debug_level) {
      printk("[TM][pm_set_g988_inport_equal_outport_staen]input invalid parameter!\n");
    }
  }
  return 1;
}

