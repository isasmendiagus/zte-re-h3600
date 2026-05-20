// module: tm.ko
// function: pm_get_g988_cfg @ 0x34ab8
// size: 296 bytes
//

undefined4 pm_get_g988_cfg(uint *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  uVar2 = *param_1;
  if (uVar2 < 4) {
    if ((param_1[4] < 8) && (param_1[3] < 2)) {
      bVar3 = 1 < (byte)param_1[2];
    }
    else {
      bVar3 = true;
    }
    if (uVar2 != 1) goto LAB_00034b10;
LAB_00034ae0:
    if (0xffe < param_1[6]) goto LAB_00034af0;
  }
  else {
    bVar3 = true;
LAB_00034b10:
    if (uVar2 == 2) {
      if (7 < param_1[5]) goto LAB_00034af0;
    }
    else if (uVar2 == 3) {
      if (7 < param_1[5]) goto LAB_00034af0;
      goto LAB_00034ae0;
    }
  }
  if (!bVar3) {
    iVar1 = pm_select_g988_reg(param_1,1,param_2);
    if (iVar1 != 0) {
      if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7379,"pm_get_g988_cfg"), iVar1 != 0))
      {
        printk("[TM][pm_get_g988_cfg]failed\n");
      }
      return 0xffffffff;
    }
    return 0;
  }
LAB_00034af0:
  if (g_tm_debug_level == 0) {
    return 1;
  }
  printk("[TM][pm_get_g988_cfg]input invalid parameter!\n");
  return 1;
}

