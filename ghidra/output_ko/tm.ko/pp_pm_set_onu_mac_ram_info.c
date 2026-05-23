// module: tm.ko
// function: pp_pm_set_onu_mac_ram_info @ 0x2fb58
// size: 396 bytes
//

undefined4 pp_pm_set_onu_mac_ram_info(uint param_1,undefined1 *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  bool bVar10;
  int local_24 [2];
  
  uVar9 = 0;
  local_24[0] = 0;
  if (g_tm_debug_level < 7) {
    if (0xf < param_1) {
LAB_0002fb8c:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_set_onu_mac_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
  }
  else {
    printk("[TM][pp_pm_set_onu_mac_ram_info]input: index = %d, onu_mac_addr: 0x%x:%x:%x;%x:%x:%x\n",
           param_1,*param_2,param_2[1],param_2[2],param_2[3],param_2[4],param_2[5]);
    if (0xf < param_1) goto LAB_0002fb8c;
    if (local_24[0] != 0) goto LAB_0002fbf4;
  }
  uVar8 = 0;
  uVar9 = 0;
  do {
    uVar8 = uVar8 + 1;
    uVar5 = pp_pm_ind_acc_done_get(local_24);
    uVar9 = uVar9 | uVar5;
    bVar10 = uVar8 == 0x13;
    if (uVar8 < 0x14) {
      bVar10 = local_24[0] == 0;
    }
  } while (bVar10);
  if (0x13 < uVar8) {
    if (g_tm_debug_level < 7) {
      return 0xffffffff;
    }
    printk("[TM][pp_pm_set_onu_mac_ram_info]indirect access time out\n");
    return 0xffffffff;
  }
LAB_0002fbf4:
  iVar6 = pp_pm_set_indirect_cmd(0,0xc,param_1);
  if (iVar6 == 0 && uVar9 == 0) {
    bVar1 = param_2[3];
    bVar2 = param_2[4];
    bVar3 = param_2[5];
    bVar4 = param_2[2];
    iVar6 = pp_pm_ind_acc_data_set(1,CONCAT11(*param_2,param_2[1]));
    iVar7 = pp_pm_ind_acc_data_set
                      (0,(uint)bVar1 << 0x10 | (uint)bVar2 << 8 | (uint)bVar3 | (uint)bVar4 << 0x18)
    ;
    if (iVar7 == 0 && iVar6 == 0) {
      return 0;
    }
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_set_onu_mac_ram_info]indirect access failed\n");
  }
  return 0xffffffff;
}

