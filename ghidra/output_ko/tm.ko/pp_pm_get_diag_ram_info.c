// module: tm.ko
// function: pp_pm_get_diag_ram_info @ 0x2fec8
// size: 440 bytes
//

undefined4 pp_pm_get_diag_ram_info(uint param_1,undefined4 *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  bool bVar6;
  int local_1c;
  
  uVar4 = 0;
  local_1c = 0;
  if (g_tm_debug_level < 7) {
    if (3 < param_1) {
LAB_0002fefc:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_diag_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
  }
  else {
    printk("[TM][pp_pm_get_diag_ram_info]input: index = %d\n",param_1);
    if (3 < param_1) goto LAB_0002fefc;
    if (local_1c != 0) goto LAB_0002ff64;
  }
  uVar3 = 0;
  uVar4 = 0;
  do {
    uVar3 = uVar3 + 1;
    uVar1 = pp_pm_ind_acc_done_get(&local_1c);
    uVar4 = uVar4 | uVar1;
    bVar6 = uVar3 == 0x13;
    if (uVar3 < 0x14) {
      bVar6 = local_1c == 0;
    }
  } while (bVar6);
  if (0x13 < uVar3) {
    if (6 < g_tm_debug_level) {
      printk("[TM][pp_pm_get_diag_ram_info]indirect access time out\n");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
LAB_0002ff64:
  iVar2 = pp_pm_set_indirect_cmd(1,0xd,param_1);
  if (iVar2 == 0 && uVar4 == 0) {
    iVar2 = 8;
    uVar4 = 0;
    puVar5 = param_2 + 7;
    do {
      iVar2 = iVar2 + -1;
      uVar3 = pp_pm_ind_acc_data_get(iVar2,puVar5);
      uVar4 = uVar4 | uVar3;
      puVar5 = puVar5 + -1;
    } while (iVar2 != 0);
    if (uVar4 == 0) {
      if ((6 < g_tm_debug_level) &&
         (printk("0x%08x 0x%08x 0x%08x 0x%08x\n",param_2[7],param_2[6],param_2[5],param_2[4]),
         6 < g_tm_debug_level)) {
        printk("0x%08x 0x%08x 0x%08x 0x%08x\n",param_2[3],param_2[2],param_2[1],*param_2);
        return 0;
      }
      return 0;
    }
  }
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][pp_pm_get_diag_ram_info]indirect access failed\n");
  return 0xffffffff;
}

