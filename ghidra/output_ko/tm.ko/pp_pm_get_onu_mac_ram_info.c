// module: tm.ko
// function: pp_pm_get_onu_mac_ram_info @ 0x2fce4
// size: 484 bytes
//

undefined4 pp_pm_get_onu_mac_ram_info(uint param_1,undefined1 *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  int local_24;
  uint local_20;
  uint local_1c;
  
  local_20 = 0;
  local_1c = 0;
  local_24 = 0;
  if (g_tm_debug_level < 7) {
    if (0xf < param_1) {
LAB_0002fd20:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_onu_mac_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
LAB_0002fd40:
    uVar2 = 0;
    do {
      uVar2 = uVar2 + 1;
      pp_pm_ind_acc_done_get(&local_24);
      bVar4 = uVar2 == 0x13;
      if (uVar2 < 0x14) {
        bVar4 = local_24 == 0;
      }
    } while (bVar4);
    if (0x13 < uVar2) goto LAB_0002fd6c;
  }
  else {
    printk("[TM][pp_pm_get_onu_mac_ram_info]input: index = %d\n",param_1);
    if (0xf < param_1) goto LAB_0002fd20;
    if (local_24 == 0) goto LAB_0002fd40;
  }
  pp_pm_set_indirect_cmd(1,0xc,param_1);
  if (local_24 != 0) {
LAB_0002fdd0:
    iVar3 = pp_pm_ind_acc_data_get(0,&local_20);
    iVar1 = pp_pm_ind_acc_data_get(1,&local_1c);
    if (iVar1 != 0 || iVar3 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_onu_mac_ram_info]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    param_2[3] = (char)(local_20 >> 0x10);
    param_2[2] = (char)(local_20 >> 0x18);
    param_2[1] = (char)local_1c;
    *param_2 = (char)(local_1c >> 8);
    uVar2 = g_tm_debug_level;
    param_2[5] = (char)local_20;
    param_2[4] = (char)(local_20 >> 8);
    if (6 < uVar2) {
      printk("[TM][pp_pm_get_onu_mac_ram_info]output: next_mac: 0x%x:%x:%x;%x:%x:%x\n",
             local_1c >> 8 & 0xff,local_1c & 0xff,local_20 >> 0x18,local_20 >> 0x10 & 0xff,
             local_20 >> 8 & 0xff,local_20 & 0xff);
      return 0;
    }
    return 0;
  }
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    pp_pm_ind_acc_done_get(&local_24);
    if (local_24 != 0) {
      if (iVar3 != 0x14) goto LAB_0002fdd0;
      break;
    }
  } while (iVar3 != 0x14);
LAB_0002fd6c:
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_get_onu_mac_ram_info]indirect access time out\n");
  }
  return 0xffffffff;
}

