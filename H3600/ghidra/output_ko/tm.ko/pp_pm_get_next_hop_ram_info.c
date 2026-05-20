// module: tm.ko
// function: pp_pm_get_next_hop_ram_info @ 0x2d950
// size: 568 bytes
//

uint pp_pm_get_next_hop_ram_info(uint param_1,undefined1 *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  int local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_30 = 0;
  if (g_tm_debug_level < 7) {
    if (0x1ff < param_1) {
LAB_0002d990:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_next_hop_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
LAB_0002d9b0:
    uVar4 = 0;
    do {
      uVar4 = uVar4 + 1;
      pp_pm_ind_acc_done_get(&local_30);
      bVar6 = uVar4 == 0x13;
      if (uVar4 < 0x14) {
        bVar6 = local_30 == 0;
      }
    } while (bVar6);
    if (0x13 < uVar4) goto LAB_0002d9dc;
  }
  else {
    printk("[TM][pp_pm_get_next_hop_ram_info]input: next_hop_idx = %d, \n",param_1);
    if (0x1ff < param_1) goto LAB_0002d990;
    if (local_30 == 0) goto LAB_0002d9b0;
  }
  pp_pm_set_indirect_cmd(1,1,param_1);
  if (local_30 != 0) {
LAB_0002da40:
    iVar5 = pp_pm_ind_acc_data_get(0,&local_2c);
    iVar1 = pp_pm_ind_acc_data_get(1,&local_28);
    iVar2 = pp_pm_ind_acc_data_get(2,&local_24);
    if ((iVar1 != 0 || iVar5 != 0) || iVar2 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_next_hop_ram_info]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    param_2[3] = (char)(local_28 >> 0x10);
    param_2[2] = (char)(local_28 >> 0x18);
    param_2[1] = (char)local_24;
    *param_2 = (char)(local_24 >> 8);
    uVar4 = g_tm_debug_level;
    param_2[5] = (char)local_28;
    param_2[4] = (char)(local_28 >> 8);
    param_2[9] = (char)local_2c;
    param_2[8] = (char)(local_2c >> 8);
    uVar3 = uVar4;
    if (uVar4 < 7) {
      uVar3 = 0;
    }
    param_2[7] = (char)(local_2c >> 0x10);
    param_2[6] = (char)(local_2c >> 0x18);
    if (6 < uVar4) {
      printk("[TM][pp_pm_get_next_hop_ram_info]output: next_mac: 0x%x:%x:%x;%x:%x:%x,  next_dip: %d.%d.%d.%d\n"
             ,local_24 >> 8 & 0xff,local_24 & 0xff,local_28 >> 0x18,local_28 >> 0x10 & 0xff,
             local_28 >> 8 & 0xff,local_28 & 0xff,local_2c >> 0x18,local_2c >> 0x10 & 0xff,
             local_2c >> 8 & 0xff,local_2c & 0xff);
      return 0;
    }
    return uVar3;
  }
  iVar5 = 0;
  do {
    iVar5 = iVar5 + 1;
    pp_pm_ind_acc_done_get(&local_30);
    if (local_30 != 0) {
      if (iVar5 != 0x14) goto LAB_0002da40;
      break;
    }
  } while (iVar5 != 0x14);
LAB_0002d9dc:
  if (g_tm_debug_level != 0) {
    printk("[TM][pp_pm_get_next_hop_ram_info]indirect access time out\n");
  }
  return 0xffffffff;
}

