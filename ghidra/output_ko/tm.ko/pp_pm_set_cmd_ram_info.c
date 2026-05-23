// module: tm.ko
// function: pp_pm_set_cmd_ram_info @ 0x2e0ac
// size: 412 bytes
//

undefined4
pp_pm_set_cmd_ram_info
          (uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
          uint param_7)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  int local_24;
  
  local_24 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][uopc_set_cmd_ram]input: cmd_addr = %d, dat_type = %d, last_cmd = %d,            tcp_checkusum_up = %d, ip_checkusum_up = %d,modify_cmd = %d, modify_data = %d\n"
           ,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  }
  bVar6 = 2 < param_2;
  if (param_2 < 4) {
    bVar6 = 0x1fff < param_1;
  }
  if (!bVar6) {
    uVar4 = param_4;
    if (param_4 < 2) {
      uVar4 = param_3;
    }
    if (uVar4 < 2) {
      bVar6 = param_5 != 0;
      if (param_5 < 2) {
        bVar6 = 0xffff < param_7;
      }
      if (0x1c < param_6) {
        bVar6 = true;
      }
      if (!bVar6) {
        uVar4 = 0;
        if (local_24 == 0) {
          uVar4 = 0;
          uVar5 = 0;
          do {
            uVar5 = uVar5 + 1;
            uVar1 = pp_pm_ind_acc_done_get(&local_24);
            uVar4 = uVar4 | uVar1;
            bVar6 = uVar5 == 0x13;
            if (uVar5 < 0x14) {
              bVar6 = local_24 == 0;
            }
          } while (bVar6);
          if (0x13 < uVar5) {
            if (g_tm_debug_level == 0) {
              return 0xffffffff;
            }
            printk("[TM][uopc_set_cmd_ram]indirect access time out\n");
            return 0xffffffff;
          }
        }
        iVar2 = pp_pm_set_indirect_cmd(0,3,param_1);
        iVar3 = pp_pm_ind_acc_data_set
                          (0,param_7 | param_6 << 0x10 | param_5 << 0x15 | param_4 << 0x16 |
                             param_3 << 0x17 | param_2 << 0x18);
        if ((iVar2 != 0 || uVar4 != 0) || iVar3 != 0) {
          if (g_tm_debug_level != 0) {
            printk("[TM][uopc_set_cmd_ram]indirect access failed\n");
          }
          return 0xffffffff;
        }
        return 0;
      }
    }
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][uopc_set_cmd_ram]input invalid parameter!\n");
  }
  return 1;
}

