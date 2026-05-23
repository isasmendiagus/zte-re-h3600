// module: tm.ko
// function: pm_set_g988_cfg @ 0x34974
// size: 316 bytes
//

undefined4 pm_set_g988_cfg(uint *param_1)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  undefined4 local_c;
  
  bVar3 = false;
  local_c = 0;
  uVar2 = *param_1;
  if ((((1 < param_1[1]) || (3 < uVar2)) || (7 < param_1[4])) ||
     ((1 < param_1[3] || (1 < (byte)param_1[2])))) {
    bVar3 = true;
  }
  if (uVar2 == 1) {
LAB_00034a30:
    if (0xffe < param_1[6]) goto LAB_000349b8;
  }
  else if (uVar2 == 2) {
    if (7 < param_1[5]) goto LAB_000349b8;
  }
  else if (uVar2 == 3) {
    if (7 < param_1[5]) goto LAB_000349b8;
    goto LAB_00034a30;
  }
  if (!bVar3) {
    iVar1 = pm_select_g988_reg(param_1,0,&local_c);
    if (iVar1 != 0) {
      if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7371,"pm_set_g988_cfg"), iVar1 != 0))
      {
        printk("[TM][pm_set_g988_cfg]failed\n");
      }
      return 0xffffffff;
    }
    return 0;
  }
LAB_000349b8:
  if (g_tm_debug_level != 0) {
    printk("[TM][pm_set_g988_cfg]input invalid parameter!\n");
  }
  return 1;
}

