// module: tm.ko
// function: pp_pm_get_pppoe_session_id_ram_info @ 0x2f350
// size: 412 bytes
//

undefined4 pp_pm_get_pppoe_session_id_ram_info(uint param_1,undefined4 *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  undefined4 local_28;
  int local_24 [2];
  
  uVar2 = 0;
  local_28 = 0;
  local_24[0] = 0;
  if (g_tm_debug_level < 7) {
    if (0xf < param_1) {
LAB_0002f388:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_pppoe_session_id_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
LAB_0002f3a8:
    uVar3 = 0;
    uVar2 = 0;
    do {
      uVar3 = uVar3 + 1;
      uVar1 = pp_pm_ind_acc_done_get(local_24);
      uVar2 = uVar2 | uVar1;
      bVar5 = uVar3 == 0x13;
      if (uVar3 < 0x14) {
        bVar5 = local_24[0] == 0;
      }
    } while (bVar5);
    if (0x13 < uVar3) goto LAB_0002f3dc;
  }
  else {
    printk("[TM][pp_pm_get_pppoe_session_id_ram_info]input: index = %d\n",param_1);
    if (0xf < param_1) goto LAB_0002f388;
    if (local_24[0] == 0) goto LAB_0002f3a8;
  }
  uVar3 = pp_pm_set_indirect_cmd(1,9,param_1);
  uVar3 = uVar3 | uVar2;
  if (local_24[0] != 0) {
LAB_0002f448:
    iVar4 = pp_pm_ind_acc_data_get(0,&local_28);
    if (iVar4 != 0 || uVar3 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_pppoe_session_id_ram_info]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    *param_2 = local_28;
    if (6 < g_tm_debug_level) {
      printk("[TM][pp_pm_get_pppoe_session_id_ram_info]output: pppoe_session_id = %d\n");
      return 0;
    }
    return 0;
  }
  iVar4 = 0;
  do {
    iVar4 = iVar4 + 1;
    uVar2 = pp_pm_ind_acc_done_get(local_24);
    uVar3 = uVar3 | uVar2;
    if (local_24[0] != 0) {
      if (iVar4 != 0x14) goto LAB_0002f448;
      break;
    }
  } while (iVar4 != 0x14);
LAB_0002f3dc:
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_get_pppoe_session_id_ram_info]indirect access time out\n");
  }
  return 0xffffffff;
}

