// module: tm.ko
// function: pp_pm_set_sub_ram_info @ 0x2e808
// size: 460 bytes
//

undefined4 pp_pm_set_sub_ram_info(uint param_1,undefined4 *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  int local_24 [2];
  
  local_24[0] = 0;
  if ((6 < g_tm_debug_level) &&
     (printk("[TM][pp_pm_set_sub_ram_info]input: sub_index = %d\n",param_1), 6 < g_tm_debug_level))
  {
    uVar7 = (uint)*(byte *)((int)param_2 + 1);
    printk("[TM][pp_pm_set_sub_ram_info]input: dscp_tc_val = %d, dscp_tc_en= %d, dei_en = %d, dslite_en = %d, pppoe_en = %d\n"
           ,*(undefined1 *)param_2,uVar7 & 1,(uVar7 << 0x1e) >> 0x1f,(uVar7 << 0x1d) >> 0x1f,
           (uVar7 << 0x1c) >> 0x1f);
    if (6 < g_tm_debug_level) {
      printk("[TM][pp_pm_set_sub_ram_info]input: v6rd_en = %d, cmd_addr = %d, vlan_addr = %d, modi_dat_addr = %d, swap_en = %d\n"
             ,((uint)*(byte *)((int)param_2 + 1) << 0x1b) >> 0x1f,
             (uint)*(byte *)((int)param_2 + 2) << 3 | (uint)(*(byte *)((int)param_2 + 1) >> 5) |
             (*(byte *)((int)param_2 + 3) & 3) << 0xb,
             (*(byte *)(param_2 + 1) & 0xf) << 6 | (uint)(*(byte *)((int)param_2 + 3) >> 2),
             (*(byte *)((int)param_2 + 5) & 0x1f) << 4 | (uint)(*(byte *)(param_2 + 1) >> 4),
             ((uint)*(byte *)((int)param_2 + 5) << 0x1a) >> 0x1f);
    }
  }
  if (param_1 < 0x400) {
    if (local_24[0] == 0) {
      uVar6 = 0;
      uVar7 = 0;
      do {
        uVar6 = uVar6 + 1;
        uVar1 = pp_pm_ind_acc_done_get(local_24);
        uVar7 = uVar7 | uVar1;
        bVar8 = uVar6 == 0x13;
        if (uVar6 < 0x14) {
          bVar8 = local_24[0] == 0;
        }
      } while (bVar8);
      if (0x13 < uVar6) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][pp_pm_set_sub_ram_info]indirect access time out\n");
        return 0xffffffff;
      }
    }
    else {
      uVar7 = 0;
    }
    iVar3 = pp_pm_set_indirect_cmd(0,6,param_1);
    iVar4 = pp_pm_ind_acc_data_set(1,param_2[1]);
    iVar5 = pp_pm_ind_acc_data_set(0,*param_2);
    uVar2 = 0;
    if (((iVar3 != 0 || uVar7 != 0) || iVar4 != 0) || iVar5 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_set_sub_ram_info]indirect access failed\n");
      }
      return 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][pp_pm_set_sub_ram_info]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}

