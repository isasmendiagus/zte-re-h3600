// module: tm.ko
// function: pp_pm_set_v6rd_cmd_info @ 0x2ef0c
// size: 352 bytes
//

undefined4 pp_pm_set_v6rd_cmd_info(uint param_1,byte *param_2)

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
LAB_0002ef40:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_set_v6rd_cmd_info]input invalid parameter!\n");
      }
      return 1;
    }
  }
  else {
    printk("[TM][pp_pm_set_v6rd_cmd_info]input: cmd_index = %d, dest_ip_addr: %d.%d.%d.%d\n",param_1
           ,*param_2,param_2[1],param_2[2],param_2[3]);
    if (0xf < param_1) goto LAB_0002ef40;
    if (local_1c != 0) goto LAB_0002efa8;
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
    printk("[TM][pp_pm_set_v6rd_cmd_info]indirect access time out\n");
    return 0xffffffff;
  }
LAB_0002efa8:
  iVar2 = pp_pm_set_indirect_cmd(0,8,param_1);
  if ((iVar2 == 0 && uVar4 == 0) &&
     (iVar2 = pp_pm_ind_acc_data_set
                        (0,(uint)param_2[1] << 0x10 | (uint)param_2[2] << 8 | (uint)param_2[3] |
                           (uint)*param_2 << 0x18), iVar2 == 0)) {
    return 0;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_set_v6rd_cmd_info]indirect access failed\n");
  }
  return 0xffffffff;
}

