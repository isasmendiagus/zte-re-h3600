// module: tm.ko
// function: pp_pm_get_v6rd_cmd_info @ 0x2f06c
// size: 436 bytes
//

undefined4 pp_pm_get_v6rd_cmd_info(uint param_1,undefined1 *param_2)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  uint local_20;
  int local_1c;
  
  local_20 = 0;
  local_1c = 0;
  if (g_tm_debug_level < 7) {
    if (0xf < param_1) {
LAB_0002f0a4:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_v6rd_cmd_info]input invalid parameter!\n");
      }
      return 1;
    }
LAB_0002f0c4:
    uVar1 = 0;
    do {
      uVar1 = uVar1 + 1;
      pp_pm_ind_acc_done_get(&local_1c);
      bVar3 = uVar1 == 0x13;
      if (uVar1 < 0x14) {
        bVar3 = local_1c == 0;
      }
    } while (bVar3);
    if (0x13 < uVar1) goto LAB_0002f0f0;
  }
  else {
    printk("[TM][pp_pm_get_v6rd_cmd_info]input: cmd_index = %d\n",param_1);
    if (0xf < param_1) goto LAB_0002f0a4;
    if (local_1c == 0) goto LAB_0002f0c4;
  }
  pp_pm_set_indirect_cmd(1,8,param_1);
  if (local_1c != 0) {
LAB_0002f154:
    iVar2 = pp_pm_ind_acc_data_get(0,&local_20);
    if (iVar2 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_v6rd_cmd_info]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    param_2[3] = (char)local_20;
    param_2[2] = (char)(local_20 >> 8);
    param_2[1] = (char)(local_20 >> 0x10);
    *param_2 = (char)(local_20 >> 0x18);
    if (6 < g_tm_debug_level) {
      printk("[TM][pp_pm_get_next_hop_ram_info]output: dest_ip_addr: %d.%d.%d.%d\n",local_20 >> 0x18
             ,local_20 >> 0x10 & 0xff,local_20 >> 8 & 0xff,local_20 & 0xff);
      return 0;
    }
    return 0;
  }
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    pp_pm_ind_acc_done_get(&local_1c);
    if (local_1c != 0) {
      if (iVar2 != 0x14) goto LAB_0002f154;
      break;
    }
  } while (iVar2 != 0x14);
LAB_0002f0f0:
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_get_v6rd_cmd_info]indirect access time out\n");
  }
  return 0xffffffff;
}

