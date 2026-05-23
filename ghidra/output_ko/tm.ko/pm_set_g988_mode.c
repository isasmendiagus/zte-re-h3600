// module: tm.ko
// function: pm_set_g988_mode @ 0x33764
// size: 204 bytes
//

undefined4 pm_set_g988_mode(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  if (g_tm_debug_level < 7) {
    bVar3 = 1 < param_1;
    bVar2 = param_1 == 2;
    if (param_1 < 3) {
      bVar3 = 2 < param_2;
      bVar2 = param_2 == 3;
    }
    if (!bVar3 || bVar2) {
LAB_000337a0:
      iVar1 = tmOnuRegWrite(3,param_2,param_1,pmRegTable);
      if (iVar1 == 0) {
        return 0;
      }
      if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7184,"pm_set_g988_mode"), iVar1 != 0)
         ) {
        printk("[TM][pm_set_g988_mode]reg write failed\n");
      }
      return 0xffffffff;
    }
  }
  else {
    printk("[TM][pm_set_g988_mode]input: mode = %d\n",param_2,param_1);
    bVar3 = 1 < param_1;
    bVar2 = param_1 == 2;
    if (param_1 < 3) {
      bVar3 = 2 < param_2;
      bVar2 = param_2 == 3;
    }
    if (!bVar3 || bVar2) goto LAB_000337a0;
    if (6 < g_tm_debug_level) {
      printk("[TM][pm_set_g988_mode]input invalid parameter!\n");
    }
  }
  return 1;
}

