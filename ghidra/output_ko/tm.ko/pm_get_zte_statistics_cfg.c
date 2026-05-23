// module: tm.ko
// function: pm_get_zte_statistics_cfg @ 0x351dc
// size: 496 bytes
//

undefined4 pm_get_zte_statistics_cfg(int *param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_64;
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
  iVar1 = pm_get_zte_cfg(param_1,&local_64);
  if (iVar1 == 0) {
    if (param_1[1] == 0) {
      printk("This zte rule is not enable!\n");
      return 0xffffffff;
    }
    if (*param_1 == 0) {
      uVar2 = 2;
    }
    else {
      uVar2 = 3;
    }
    iVar1 = pm_get_indirect_data(uVar2,local_64,&local_60);
    if (iVar1 == 0) {
      if (*param_1 == 1) {
        *param_2 = local_60;
        param_2[4] = local_54;
        param_2[2] = local_5c;
        param_2[3] = local_58;
        param_2[5] = local_50;
        param_2[6] = local_4c;
        param_2[9] = local_48;
        param_2[10] = local_44;
        param_2[0xb] = local_40;
        param_2[0xc] = local_3c;
        return 0;
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
      return 0;
    }
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7444,"pm_get_zte_statistics_cfg"), iVar1 != 0)) {
      printk("[TM][pm_get_zte_statistics_cfg]indirect access failed\n");
      return 0xffffffff;
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar1 = ___ratelimit(_rs_7441,"pm_get_zte_statistics_cfg"), iVar1 != 0)) {
    printk("[TM][pm_get_zte_statistics_cfg] failed\n");
  }
  return 0xffffffff;
}

