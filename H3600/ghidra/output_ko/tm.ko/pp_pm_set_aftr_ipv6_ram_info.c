// module: tm.ko
// function: pp_pm_set_aftr_ipv6_ram_info @ 0x2f824
// size: 376 bytes
//

undefined4 pp_pm_set_aftr_ipv6_ram_info(uint param_1,undefined4 *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  int local_1c;
  
  uVar7 = 0;
  local_1c = 0;
  if (g_tm_debug_level < 7) {
    if (0xf < param_1) {
LAB_0002f858:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_set_aftr_ipv6_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
  }
  else {
    printk("[TM][pp_pm_set_aftr_ipv6_ram_info]input: index = %d, aftr_ipv6_addr:0x%x 0x%x 0x%x 0x%x\n"
           ,param_1,*param_2,param_2[1],param_2[2],param_2[3]);
    if (0xf < param_1) goto LAB_0002f858;
    if (local_1c != 0) goto LAB_0002f8c0;
  }
  uVar6 = 0;
  uVar7 = 0;
  do {
    uVar6 = uVar6 + 1;
    uVar1 = pp_pm_ind_acc_done_get(&local_1c);
    uVar7 = uVar7 | uVar1;
    bVar8 = uVar6 == 0x13;
    if (uVar6 < 0x14) {
      bVar8 = local_1c == 0;
    }
  } while (bVar8);
  if (0x13 < uVar6) {
    if (g_tm_debug_level < 7) {
      return 0xffffffff;
    }
    printk("[TM][pp_pm_set_aftr_ipv6_ram_info]indirect access time out\n");
    return 0xffffffff;
  }
LAB_0002f8c0:
  iVar2 = pp_pm_set_indirect_cmd(0,0xb,param_1);
  if (iVar2 == 0 && uVar7 == 0) {
    iVar2 = pp_pm_ind_acc_data_set(3,param_2[3]);
    iVar3 = pp_pm_ind_acc_data_set(2,param_2[2]);
    iVar4 = pp_pm_ind_acc_data_set(1,param_2[1]);
    iVar5 = pp_pm_ind_acc_data_set(0,*param_2);
    if (((iVar3 == 0 && iVar2 == 0) && iVar4 == 0) && iVar5 == 0) {
      return 0;
    }
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_set_aftr_ipv6_ram_info]indirect access failed\n");
  }
  return 0xffffffff;
}

