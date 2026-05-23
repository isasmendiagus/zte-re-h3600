// module: tm.ko
// function: pp_pm_get_vlan_modify_ram_info @ 0x2dd34
// size: 476 bytes
//

undefined4 pp_pm_get_vlan_modify_ram_info(uint param_1,undefined1 *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  uint local_20;
  int local_1c;
  
  uVar4 = 0;
  local_1c = 0;
  if (param_1 < 0x400) {
    uVar5 = 0;
    do {
      uVar4 = uVar4 + 1;
      uVar2 = pp_pm_ind_acc_done_get(&local_1c);
      uVar5 = uVar5 | uVar2;
      bVar6 = uVar4 == 0x13;
      if (uVar4 < 0x14) {
        bVar6 = local_1c == 0;
      }
    } while (bVar6);
    if (uVar4 < 0x14) {
      uVar4 = pp_pm_set_indirect_cmd(1,2,param_1);
      uVar4 = uVar4 | uVar5;
      iVar3 = 0;
      if (local_1c != 0) {
LAB_0002de10:
        iVar3 = pp_pm_ind_acc_data_get(0,&local_20);
        *param_2 = (char)(local_20 & 0xfff);
        param_2[1] = (byte)((local_20 << 0x14) >> 0x1c) | (byte)((local_20 >> 0xc & 1) << 4) |
                     (byte)((local_20 >> 0xd & 7) << 5);
        param_2[3] = (byte)((local_20 << 4) >> 0x1c) | (byte)((local_20 >> 0x1c & 1) << 4) |
                     (byte)((local_20 >> 0x1d) << 5);
        param_2[2] = (char)(local_20 >> 0x10);
        if (iVar3 == 0 && uVar4 == 0) {
          if (g_tm_debug_level < 7) {
            return 0;
          }
          printk("[TM][pp_pm_get_vlan_modify_ram_info]output: C_VID = %d, C_CFI = %d, C_PRI = %d, S_VID = %d, S_CFI = %d, S_PRI = %d\n"
                 ,local_20 & 0xfff,local_20 >> 0xc & 1,local_20 >> 0xd & 7,local_20 >> 0x10 & 0xfff,
                 local_20 >> 0x1c & 1,local_20 >> 0x1d);
          return 0;
        }
        if (g_tm_debug_level < 7) {
          return 0xffffffff;
        }
        printk("[TM][pp_pm_get_vlan_modify_ram_info]indirect access failed\n");
        return 0xffffffff;
      }
      do {
        iVar3 = iVar3 + 1;
        uVar5 = pp_pm_ind_acc_done_get(&local_1c);
        uVar4 = uVar4 | uVar5;
        if (local_1c != 0) {
          if (iVar3 != 0x14) goto LAB_0002de10;
          break;
        }
      } while (iVar3 != 0x14);
    }
    if (g_tm_debug_level < 7) {
      return 0xffffffff;
    }
    printk("[TM][pp_pm_get_vlan_modify_ram_info]indirect access time out\n");
    uVar1 = 0xffffffff;
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][pp_pm_get_vlan_modify_ram_info]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

