// module: tm.ko
// function: pp_pm_set_pppoe_session_id_ram_info @ 0x2f220
// size: 304 bytes
//

undefined4 pp_pm_set_pppoe_session_id_ram_info(uint param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  int local_1c;
  
  uVar4 = 0;
  local_1c = 0;
  if (g_tm_debug_level < 7) {
    if (0xf < param_1) {
LAB_0002f254:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_set_pppoe_session_id_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
  }
  else {
    printk("[TM][pp_pm_set_pppoe_session_id_ram_info]input: index = %d, pppoe_session_id = %d\n",
           param_1,param_2);
    if (0xf < param_1) goto LAB_0002f254;
    if (local_1c != 0) goto LAB_0002f2bc;
  }
  uVar3 = 0;
  uVar4 = 0;
  do {
    uVar3 = uVar3 + 1;
    uVar1 = pp_pm_ind_acc_done_get(&local_1c);
    uVar4 = uVar4 | uVar1;
    bVar5 = uVar3 == 0x13;
    if (uVar3 < 0x14) {
      bVar5 = local_1c == 0;
    }
  } while (bVar5);
  if (0x13 < uVar3) {
    if (g_tm_debug_level < 7) {
      return 0xffffffff;
    }
    printk("[TM][pp_pm_set_pppoe_session_id_ram_info]indirect access time out\n");
    return 0xffffffff;
  }
LAB_0002f2bc:
  iVar2 = pp_pm_set_indirect_cmd(0,9,param_1);
  if ((iVar2 == 0 && uVar4 == 0) && (iVar2 = pp_pm_ind_acc_data_set(0,param_2), iVar2 == 0)) {
    return 0;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_set_pppoe_session_id_ram_info]indirect access failed\n");
  }
  return 0xffffffff;
}

