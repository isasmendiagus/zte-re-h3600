// module: tm.ko
// function: pp_pm_set_e8_qos_info @ 0x2e248
// size: 324 bytes
//

undefined4 pp_pm_set_e8_qos_info(uint param_1,undefined4 *param_2)

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
LAB_0002e27c:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_set_e8_qos_info]input invalid parameter!\n");
      }
      return 1;
    }
  }
  else {
    uVar4 = (uint)*(byte *)((int)param_2 + 1);
    printk("[TM][pp_pm_set_e8_qos_info]input: qos_modi_addr = %d, qos_dscp_tc = %d,qos_dscp_en = %d, qos_pri = %d, qos_pri_en = %d\n"
           ,param_1,*(undefined1 *)param_2,uVar4 & 1,(uVar4 << 0x1c) >> 0x1d,(uVar4 << 0x1b) >> 0x1f
          );
    if (0x1ff < param_1) goto LAB_0002e27c;
    if (local_1c != 0) goto LAB_0002e2e4;
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
    printk("[TM][pp_pm_set_e8_qos_info]indirect access time out\n");
    return 0xffffffff;
  }
LAB_0002e2e4:
  iVar2 = pp_pm_set_indirect_cmd(0,4,param_1);
  iVar3 = pp_pm_ind_acc_data_set(0,*param_2);
  if ((iVar2 != 0 || uVar5 != 0) || iVar3 != 0) {
    if (6 < g_tm_debug_level) {
      printk("[TM][pp_pm_set_e8_qos_info]indirect access failed\n");
    }
    return 0xffffffff;
  }
  return 0;
}

