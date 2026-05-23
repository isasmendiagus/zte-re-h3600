// module: tm.ko
// function: pm_get_g988_statistics @ 0x357c4
// size: 344 bytes
//

undefined4 pm_get_g988_statistics(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if (0x3f < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][pm_get_g988_statistics]input invalid parameter!\n");
    }
    return 1;
  }
  iVar1 = pm_get_indirect_data(1,param_1,&local_60);
  if (iVar1 != 0) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7498,"pm_get_g988_statistics"), iVar1 != 0)) {
      printk("[TM][pm_get_g988_statistics]indirect access failed\n");
    }
    return 0xffffffff;
  }
  param_2[2] = local_5c;
  param_2[3] = local_58;
  *param_2 = local_60;
  param_2[4] = local_54;
  param_2[5] = local_50;
  param_2[6] = local_4c;
  param_2[7] = local_48;
  param_2[8] = local_44;
  param_2[9] = local_40;
  param_2[10] = local_3c;
  param_2[0xb] = local_38;
  param_2[0xc] = local_34;
  param_2[0xd] = local_30;
  param_2[0xe] = local_2c;
  return 0;
}

