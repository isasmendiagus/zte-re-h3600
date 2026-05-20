// module: tm.ko
// function: pp_pm_set_modify_ram_info @ 0x2e540
// size: 300 bytes
//

undefined4 pp_pm_set_modify_ram_info(uint param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  int local_1c;
  
  uVar5 = 0;
  local_1c = 0;
  if (g_tm_debug_level < 7) {
    if (0x1ff < param_1) {
LAB_0002e574:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_set_modify_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
  }
  else {
    printk("[TM][pp_pm_set_modify_ram_info]input: modi_addr = %d, modi_data = %d\n",param_1,param_2)
    ;
    if (0x1ff < param_1) goto LAB_0002e574;
    if (local_1c != 0) goto LAB_0002e5dc;
  }
  uVar4 = 0;
  uVar5 = 0;
  do {
    uVar4 = uVar4 + 1;
    uVar1 = pp_pm_ind_acc_done_get(&local_1c);
    uVar5 = uVar5 | uVar1;
    bVar6 = uVar4 == 0x13;
    if (uVar4 < 0x14) {
      bVar6 = local_1c == 0;
    }
  } while (bVar6);
  if (0x13 < uVar4) {
    if (g_tm_debug_level < 7) {
      return 0xffffffff;
    }
    printk("[TM][pp_pm_set_modify_ram_info]indirect access time out\n");
    return 0xffffffff;
  }
LAB_0002e5dc:
  iVar2 = pp_pm_set_indirect_cmd(0,5,param_1);
  iVar3 = pp_pm_ind_acc_data_set(0,param_2);
  if ((iVar2 != 0 || uVar5 != 0) || iVar3 != 0) {
    if (6 < g_tm_debug_level) {
      printk("[TM][pp_pm_set_modify_ram_info]indirect access failed\n");
    }
    return 0xffffffff;
  }
  return 0;
}

