// module: tm.ko
// function: pp_pm_get_b4_ipv6_ram_info @ 0x2f664
// size: 448 bytes
//

undefined4 pp_pm_get_b4_ipv6_ram_info(uint param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  int local_1c;
  
  local_1c = 0;
  if (g_tm_debug_level < 7) {
    if (0xf < param_1) {
LAB_0002f698:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_b4_ipv6_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
LAB_0002f6b8:
    uVar4 = 0;
    do {
      uVar4 = uVar4 + 1;
      pp_pm_ind_acc_done_get(&local_1c);
      bVar6 = uVar4 == 0x13;
      if (uVar4 < 0x14) {
        bVar6 = local_1c == 0;
      }
    } while (bVar6);
    if (0x13 < uVar4) goto LAB_0002f6e4;
  }
  else {
    printk("[TM][pp_pm_get_b4_ipv6_ram_info]input: index = %d\n",param_1);
    if (0xf < param_1) goto LAB_0002f698;
    if (local_1c == 0) goto LAB_0002f6b8;
  }
  pp_pm_set_indirect_cmd(1,10,param_1);
  if (local_1c != 0) {
LAB_0002f748:
    iVar5 = pp_pm_ind_acc_data_get(3,param_2 + 3);
    iVar1 = pp_pm_ind_acc_data_get(2,param_2 + 2);
    iVar2 = pp_pm_ind_acc_data_get(1,param_2 + 2);
    iVar3 = pp_pm_ind_acc_data_get(0,param_2);
    if (((iVar1 != 0 || iVar5 != 0) || iVar2 != 0) || iVar3 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_b4_ipv6_ram_info]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    if (6 < g_tm_debug_level) {
      printk("[TM][pp_pm_get_b4_ipv6_ram_info]input: b4_ipv6_addr: 0x%x 0x%x 0x%x 0x%x\n",*param_2,
             param_2[1],param_2[2],param_2[3]);
      return 0;
    }
    return 0;
  }
  iVar5 = 0;
  do {
    iVar5 = iVar5 + 1;
    pp_pm_ind_acc_done_get(&local_1c);
    if (local_1c != 0) {
      if (iVar5 != 0x14) goto LAB_0002f748;
      break;
    }
  } while (iVar5 != 0x14);
LAB_0002f6e4:
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_get_b4_ipv6_ram_info]indirect access time out\n");
  }
  return 0xffffffff;
}

