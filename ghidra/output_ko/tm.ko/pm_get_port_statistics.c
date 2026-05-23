// module: tm.ko
// function: pm_get_port_statistics @ 0x3559c
// size: 352 bytes
//

undefined4 pm_get_port_statistics(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_40;
  uint local_3c;
  undefined4 local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  switch(param_2) {
  case 0:
    iVar3 = 0;
    break;
  case 1:
    iVar3 = 3;
    break;
  case 2:
    iVar3 = 6;
    break;
  case 3:
    iVar3 = 9;
    break;
  case 4:
    iVar3 = 0xc;
    break;
  case 5:
    iVar3 = 0xf;
    break;
  case 6:
    iVar3 = 0x12;
    break;
  case 7:
    iVar3 = 0x15;
    break;
  default:
    return 1;
  }
  if (param_1 == 1) {
    iVar3 = iVar3 + 0x18;
  }
  iVar1 = pm_get_indirect_data(0,iVar3,&local_40);
  iVar2 = pm_get_indirect_data(0,iVar3 + 1,&local_38);
  iVar3 = pm_get_indirect_data(0,iVar3 + 2,&local_30);
  if ((iVar2 != 0 || iVar1 != 0) || iVar3 != 0) {
    if ((g_tm_debug_level != 0) &&
       (iVar3 = ___ratelimit(_rs_7480,"pm_get_port_statistics"), iVar3 != 0)) {
      printk("[TM][pm_get_port_statistics_cfg]indirect access failed\n");
    }
    return 0xffffffff;
  }
  param_3[2] = local_3c >> 4;
  *param_3 = local_40;
  param_3[1] = local_3c & 0xf;
  param_3[6] = local_34 >> 4;
  param_3[4] = local_38;
  param_3[5] = local_34 & 0xf;
  param_3[8] = local_30;
  param_3[9] = local_30 & 0xf;
  param_3[10] = local_2c >> 4;
  return 0;
}

