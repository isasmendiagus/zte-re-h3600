// module: tm.ko
// function: pp_pm_get_sub_ram_info @ 0x2e9d4
// size: 572 bytes
//

undefined4 pp_pm_get_sub_ram_info(uint param_1,undefined4 *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_20 = 0;
  local_1c = 0;
  local_24 = 0;
  if (g_tm_debug_level < 7) {
    if (0x3ff < param_1) {
LAB_0002ea10:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_sub_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
LAB_0002ea30:
    uVar3 = 0;
    do {
      uVar3 = uVar3 + 1;
      pp_pm_ind_acc_done_get(&local_24);
      bVar5 = uVar3 == 0x13;
      if (uVar3 < 0x14) {
        bVar5 = local_24 == 0;
      }
    } while (bVar5);
    if (0x13 < uVar3) goto LAB_0002ea5c;
  }
  else {
    printk("[TM][pp_pm_get_sub_ram_info]input: sub_index = %d\n",param_1);
    if (0x3ff < param_1) goto LAB_0002ea10;
    if (local_24 == 0) goto LAB_0002ea30;
  }
  uVar3 = pp_pm_set_indirect_cmd(1,6,param_1);
  if (local_24 != 0) {
LAB_0002eac8:
    iVar4 = pp_pm_ind_acc_data_get(1,&local_1c);
    iVar2 = pp_pm_ind_acc_data_get(0,&local_20);
    if ((iVar4 == 0 && uVar3 == 0) && iVar2 == 0) {
      *param_2 = local_20;
      uVar3 = g_tm_debug_level;
      param_2[1] = local_1c;
      if (6 < uVar3) {
        uVar3 = (uint)*(byte *)((int)param_2 + 1);
        printk("[TM][pp_pm_get_sub_ram_info]input: dscp_tc_val = %d, dscp_tc_en= %d, dei_en = %d, dslite_en = %d, pppoe_en = %d\n"
               ,*(undefined1 *)param_2,uVar3 & 1,(uVar3 << 0x1e) >> 0x1f,(uVar3 << 0x1d) >> 0x1f,
               (uVar3 << 0x1c) >> 0x1f);
        if (6 < g_tm_debug_level) {
          printk("[TM][pp_pm_get_sub_ram_info]input: v6rd_en = %d, cmd_addr = %d, vlan_addr = %d, modi_dat_addr = %d, swap_en = %d\n"
                 ,((uint)*(byte *)((int)param_2 + 1) << 0x1b) >> 0x1f,
                 (uint)*(byte *)((int)param_2 + 2) << 3 | (uint)(*(byte *)((int)param_2 + 1) >> 5) |
                 (*(byte *)((int)param_2 + 3) & 3) << 0xb,
                 (*(byte *)(param_2 + 1) & 0xf) << 6 | (uint)(*(byte *)((int)param_2 + 3) >> 2),
                 (*(byte *)((int)param_2 + 5) & 0x1f) << 4 | (uint)(*(byte *)(param_2 + 1) >> 4),
                 ((uint)*(byte *)((int)param_2 + 5) << 0x1a) >> 0x1f);
        }
      }
      return 0;
    }
    if (g_tm_debug_level != 0) {
      printk("[TM][pp_pm_get_sub_ram_info]indirect access failed\n");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  iVar4 = 0;
  do {
    iVar4 = iVar4 + 1;
    uVar1 = pp_pm_ind_acc_done_get(&local_24);
    uVar3 = uVar3 | uVar1;
    if (local_24 != 0) {
      if (iVar4 != 0x14) goto LAB_0002eac8;
      break;
    }
  } while (iVar4 != 0x14);
LAB_0002ea5c:
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][pp_pm_get_sub_ram_info]indirect access time out\n");
  return 0xffffffff;
}

