// module: tm.ko
// function: pp_pm_set_vlan_modify_ram_info @ 0x2db88
// size: 428 bytes
//

undefined4 pp_pm_set_vlan_modify_ram_info(uint param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  int local_1c;
  
  uVar7 = 0;
  local_1c = 0;
  if (g_tm_debug_level < 7) {
    if (0x3ff < param_1) {
LAB_0002dbbc:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_set_vlan_modify_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
  }
  else {
    bVar1 = param_2[3];
    bVar2 = param_2[1];
    printk("[TM][pp_pm_set_vlan_modify_ram_info]intput:vlan_addr = %x, C_VID = %d, C_CFI = %d, C_PRI = %d, S_VID = %d, S_CFI = %d, S_PRI = %d\n"
           ,param_1,(uint)*param_2 | (bVar2 & 0xf) << 8,((uint)bVar2 << 0x1b) >> 0x1f,bVar2 >> 5,
           (uint)param_2[2] | (bVar1 & 0xf) << 8,((uint)bVar1 << 0x1b) >> 0x1f,bVar1 >> 5);
    if (0x3ff < param_1) goto LAB_0002dbbc;
    if (local_1c != 0) goto LAB_0002dc24;
  }
  uVar6 = 0;
  uVar7 = 0;
  do {
    uVar6 = uVar6 + 1;
    uVar3 = pp_pm_ind_acc_done_get(&local_1c);
    uVar7 = uVar7 | uVar3;
    bVar8 = uVar6 == 0x13;
    if (uVar6 < 0x14) {
      bVar8 = local_1c == 0;
    }
  } while (bVar8);
  if (0x13 < uVar6) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[TM][pp_pm_set_vlan_modify_ram_info]indirect access time out\n");
    return 0xffffffff;
  }
LAB_0002dc24:
  iVar4 = pp_pm_set_indirect_cmd(0,2,param_1);
  bVar1 = param_2[3];
  bVar2 = param_2[1];
  iVar5 = pp_pm_ind_acc_data_set
                    (0,(((uint)bVar1 << 0x1b) >> 0x1f) << 0x1c |
                       (((uint)bVar2 << 0x1b) >> 0x1f) << 0xc | (uint)*param_2 | (bVar2 & 0xf) << 8
                       | (uint)(bVar2 >> 5) << 0xd | ((uint)param_2[2] | (bVar1 & 0xf) << 8) << 0x10
                       | (uint)(bVar1 >> 5) << 0x1d);
  if ((iVar4 != 0 || uVar7 != 0) || iVar5 != 0) {
    if (g_tm_debug_level != 0) {
      printk("[TM][pp_pm_set_vlan_modify_ram_info]indirect access failed\n");
    }
    return 0xffffffff;
  }
  return 0;
}

