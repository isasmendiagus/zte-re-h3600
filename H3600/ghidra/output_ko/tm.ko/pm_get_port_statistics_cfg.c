// module: tm.ko
// function: pm_get_port_statistics_cfg @ 0x3444c
// size: 468 bytes
//

undefined4 pm_get_port_statistics_cfg(int *param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_40;
  uint local_3c;
  undefined4 local_38;
  uint local_34;
  undefined4 local_30;
  uint local_2c;
  
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  iVar1 = pm_get_port_cfg();
  if (iVar1 == 0) {
    if (param_1[1] == 0) {
      printk("error:This port rule is not enable!\n");
      return 0xffffffff;
    }
    switch(param_1[2]) {
    case 0:
      iVar1 = 0;
      break;
    case 1:
      iVar1 = 3;
      break;
    case 2:
      iVar1 = 6;
      break;
    case 3:
      iVar1 = 9;
      break;
    case 4:
      iVar1 = 0xc;
      break;
    case 5:
      iVar1 = 0xf;
      break;
    case 6:
      iVar1 = 0x12;
      break;
    case 7:
      iVar1 = 0x15;
      break;
    default:
      return 1;
    }
    if (*param_1 == 1) {
      iVar1 = iVar1 + 0x18;
    }
    iVar2 = pm_get_indirect_data(0,iVar1,&local_40);
    iVar3 = pm_get_indirect_data(0,iVar1 + 1,&local_38);
    iVar1 = pm_get_indirect_data(0,iVar1 + 2,&local_30);
    if ((iVar3 == 0 && iVar2 == 0) && iVar1 == 0) {
      param_2[2] = local_3c >> 4;
      *param_2 = local_40;
      param_2[1] = local_3c & 0xf;
      param_2[6] = local_34 >> 4;
      param_2[4] = local_38;
      param_2[5] = local_34 & 0xf;
      param_2[10] = local_2c >> 4;
      param_2[8] = local_30;
      param_2[9] = local_2c & 0xf;
      return 0;
    }
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7332,"pm_get_port_statistics_cfg"), iVar1 != 0)) {
      printk("[TM][pm_get_port_statistics_cfg]indirect access failed\n");
      return 0xffffffff;
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar1 = ___ratelimit(_rs_7319,"pm_get_port_statistics_cfg"), iVar1 != 0)) {
    printk("[TM][pm_get_port_statistics_cfg] failed\n");
  }
  return 0xffffffff;
}

