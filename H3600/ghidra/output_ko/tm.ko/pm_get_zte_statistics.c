// module: tm.ko
// function: pm_get_zte_statistics @ 0x359f8
// size: 416 bytes
//

undefined4 pm_get_zte_statistics(uint param_1,undefined4 *param_2)

{
  int iVar1;
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
  undefined4 local_28;
  undefined4 local_24;
  
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
  local_28 = 0;
  local_24 = 0;
  if (0x1f < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][pm_get_zte_statistics]input invalid parameter!\n");
    }
    return 1;
  }
  if (param_1 < 0x10) {
    iVar1 = pm_get_indirect_data(2,param_1,&local_58);
    if (iVar1 == 0) {
      *param_2 = local_58;
      param_2[4] = local_4c;
      param_2[2] = local_54;
      param_2[3] = local_50;
      param_2[5] = local_48;
      param_2[6] = local_44;
      param_2[9] = local_40;
      param_2[0xc] = local_3c;
      return 0;
    }
  }
  else {
    iVar1 = pm_get_indirect_data(3,param_1,&local_58);
    if (iVar1 == 0) {
      *param_2 = local_58;
      param_2[4] = local_4c;
      param_2[2] = local_54;
      param_2[3] = local_50;
      param_2[5] = local_48;
      param_2[6] = local_44;
      param_2[7] = local_40;
      param_2[8] = local_3c;
      param_2[9] = local_38;
      param_2[0xc] = local_34;
      return 0;
    }
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_7516,"pm_get_zte_statistics"), iVar1 != 0)) {
    printk("[TM][pm_get_zte_statistics]indirect access failed\n");
  }
  return 0xffffffff;
}

