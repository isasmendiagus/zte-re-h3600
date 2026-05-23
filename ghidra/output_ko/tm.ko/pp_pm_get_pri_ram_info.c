// module: tm.ko
// function: pp_pm_get_pri_ram_info @ 0x2ed58
// size: 436 bytes
//

undefined4 pp_pm_get_pri_ram_info(uint param_1,uint param_2,undefined4 *param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  undefined4 local_28;
  int local_24;
  
  local_28 = 0;
  local_24 = 0;
  if (g_tm_debug_level < 7) {
    bVar6 = 0x3e < param_2;
    bVar5 = param_2 == 0x3f;
    if (param_2 < 0x40) {
      bVar6 = 6 < param_1;
      bVar5 = param_1 == 7;
    }
    if (bVar6 && !bVar5) {
LAB_0002ed98:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_pri_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
LAB_0002edb8:
    uVar2 = 0;
    uVar4 = 0;
    do {
      uVar2 = uVar2 + 1;
      uVar1 = pp_pm_ind_acc_done_get(&local_24);
      uVar4 = uVar4 | uVar1;
      bVar5 = uVar2 == 0x13;
      if (uVar2 < 0x14) {
        bVar5 = local_24 == 0;
      }
    } while (bVar5);
    if (0x13 < uVar2) goto LAB_0002edec;
  }
  else {
    printk("[TM][pp_pm_get_pri_ram_info]input: ram_index = %d, dscp = %d\n",param_1,param_2);
    bVar6 = 0x3e < param_2;
    bVar5 = param_2 == 0x3f;
    if (param_2 < 0x40) {
      bVar6 = 6 < param_1;
      bVar5 = param_1 == 7;
    }
    if (bVar6 && !bVar5) goto LAB_0002ed98;
    uVar4 = 0;
    if (local_24 == 0) goto LAB_0002edb8;
  }
  uVar2 = pp_pm_set_indirect_cmd(1,7,param_2 + param_1 * 0x40);
  uVar2 = uVar2 | uVar4;
  if (local_24 != 0) {
LAB_0002ee58:
    iVar3 = pp_pm_ind_acc_data_get(0,&local_28);
    if (iVar3 != 0 || uVar2 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_pri_ram_info]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    *param_3 = local_28;
    if (6 < g_tm_debug_level) {
      printk("[TM][pp_pm_get_pri_ram_info]output: pri = %d\n");
      return 0;
    }
    return 0;
  }
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    uVar4 = pp_pm_ind_acc_done_get(&local_24);
    uVar2 = uVar2 | uVar4;
    if (local_24 != 0) {
      if (iVar3 != 0x14) goto LAB_0002ee58;
      break;
    }
  } while (iVar3 != 0x14);
LAB_0002edec:
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_get_pri_ram_info]indirect access time out\n");
  }
  return 0xffffffff;
}

