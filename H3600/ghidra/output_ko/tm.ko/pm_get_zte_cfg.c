// module: tm.ko
// function: pm_get_zte_cfg @ 0x35110
// size: 196 bytes
//

undefined4 pm_get_zte_cfg(uint *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = *param_1;
  if (((uVar2 < 2) && (param_1[3] < 8)) && (param_1[2] < 2)) {
    if (uVar2 == 0) {
      uVar2 = 0xffe;
      if (0xffe < param_1[4]) goto LAB_00035120;
    }
    iVar1 = pm_select_zte_reg(param_1,1,param_2,uVar2,param_4);
    if (iVar1 == 0) {
      return 0;
    }
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7431,"pm_get_zte_cfg"), iVar1 != 0)) {
      printk("[TM][pm_get_zte_cfg]failed\n");
    }
    return 0xffffffff;
  }
LAB_00035120:
  if (g_tm_debug_level == 0) {
    return 1;
  }
  printk("[TM][pm_get_zte_cfg]input invalid parameter!\n");
  return 1;
}

