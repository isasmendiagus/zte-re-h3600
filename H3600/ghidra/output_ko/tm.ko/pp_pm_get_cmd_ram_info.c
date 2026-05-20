// module: tm.ko
// function: pp_pm_get_cmd_ram_info @ 0x2df10
// size: 412 bytes
//

undefined4 pp_pm_get_cmd_ram_info(uint param_1,undefined4 *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  undefined4 local_20;
  int local_1c [2];
  
  uVar3 = 0;
  local_20 = 0;
  local_1c[0] = 0;
  if (0x1fff < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][pp_pm_get_cmd_ram_info]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  do {
    uVar3 = uVar3 + 1;
    pp_pm_ind_acc_done_get(local_1c);
    bVar4 = uVar3 == 0x13;
    if (uVar3 < 0x14) {
      bVar4 = local_1c[0] == 0;
    }
  } while (bVar4);
  if (uVar3 < 0x14) {
    uVar3 = pp_pm_set_indirect_cmd(1,3,param_1);
    iVar2 = 0;
    if (local_1c[0] != 0) {
LAB_0002dfe8:
      iVar2 = pp_pm_ind_acc_data_get(0,&local_20);
      if (iVar2 == 0 && uVar3 == 0) {
        *param_2 = local_20;
        if (6 < g_tm_debug_level) {
          uVar3 = (uint)*(byte *)((int)param_2 + 2);
          printk("[TM][pp_pm_get_cmd_ram_info]output:cmd_addr = %d, cmd_dat = %d, cmd = %d, ip_checksum_up = %d, tcp_checksum_up = %d, last_cmd = %d, dat_type = %d\n"
                 ,param_1,*(undefined2 *)param_2,uVar3 & 0x1f,(uVar3 << 0x1a) >> 0x1f,
                 (uVar3 << 0x19) >> 0x1f,*(byte *)((int)param_2 + 2) >> 7,
                 *(byte *)((int)param_2 + 3) & 3);
        }
        return 0;
      }
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][pp_pm_get_cmd_ram_info]indirect access failed\n");
      return 0xffffffff;
    }
    do {
      iVar2 = iVar2 + 1;
      uVar1 = pp_pm_ind_acc_done_get(local_1c);
      uVar3 = uVar3 | uVar1;
      if (local_1c[0] != 0) {
        if (iVar2 != 0x14) goto LAB_0002dfe8;
        break;
      }
    } while (iVar2 != 0x14);
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][pp_pm_get_cmd_ram_info]indirect access time out\n");
  }
  return 0xffffffff;
}

