// module: tm.ko
// function: pp_pm_set_pri_ram_info @ 0x2ec10
// size: 328 bytes
//

undefined4 pp_pm_set_pri_ram_info(uint param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  int local_24 [2];
  
  local_24[0] = 0;
  if (g_tm_debug_level < 7) {
    bVar6 = 0x3e < param_2;
    bVar5 = param_2 == 0x3f;
    if (param_2 < 0x40) {
      bVar6 = 6 < param_1;
      bVar5 = param_1 == 7;
    }
    if (bVar6 && !bVar5) {
LAB_0002ec4c:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_set_pri_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
  }
  else {
    printk("[TM][pp_pm_set_pri_ram_info]input: ram_index = %d, dscp = %d, pri = %d\n",param_1,
           param_2,param_3);
    bVar6 = 0x3e < param_2;
    bVar5 = param_2 == 0x3f;
    if (param_2 < 0x40) {
      bVar6 = 6 < param_1;
      bVar5 = param_1 == 7;
    }
    if (bVar6 && !bVar5) goto LAB_0002ec4c;
    uVar4 = 0;
    if (local_24[0] != 0) goto LAB_0002ecb4;
  }
  uVar3 = 0;
  uVar4 = 0;
  do {
    uVar3 = uVar3 + 1;
    uVar1 = pp_pm_ind_acc_done_get(local_24);
    uVar4 = uVar4 | uVar1;
    bVar5 = uVar3 == 0x13;
    if (uVar3 < 0x14) {
      bVar5 = local_24[0] == 0;
    }
  } while (bVar5);
  if (0x13 < uVar3) {
    if (g_tm_debug_level < 7) {
      return 0xffffffff;
    }
    printk("[TM][pp_pm_set_pri_ram_info]indirect access time out\n");
    return 0xffffffff;
  }
LAB_0002ecb4:
  iVar2 = pp_pm_set_indirect_cmd(0,7,param_2 + param_1 * 0x40);
  if ((iVar2 == 0 && uVar4 == 0) && (iVar2 = pp_pm_ind_acc_data_set(0,param_3), iVar2 == 0)) {
    return 0;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_set_pri_ram_info]indirect access failed\n");
  }
  return 0xffffffff;
}

