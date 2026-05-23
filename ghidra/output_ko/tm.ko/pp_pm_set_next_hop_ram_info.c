// module: tm.ko
// function: pp_pm_set_next_hop_ram_info @ 0x2d72c
// size: 548 bytes
//

undefined4 pp_pm_set_next_hop_ram_info(uint param_1,undefined1 *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  bool bVar15;
  int local_2c [2];
  
  uVar12 = 0;
  local_2c[0] = 0;
  if (g_tm_debug_level < 7) {
    if (0x1ff < param_1) {
LAB_0002d760:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_set_next_hop_ram_info]input invalid parameter!\n");
      }
      return 1;
    }
LAB_0002d780:
    uVar14 = 0;
    uVar12 = 0;
    do {
      uVar14 = uVar14 + 1;
      uVar9 = pp_pm_ind_acc_done_get(local_2c);
      uVar12 = uVar12 | uVar9;
      bVar15 = uVar14 == 0x13;
      if (uVar14 < 0x14) {
        bVar15 = local_2c[0] == 0;
      }
    } while (bVar15);
    if (0x13 < uVar14) goto LAB_0002d7b4;
  }
  else {
    printk("[TM][pp_pm_set_next_hop_ram_info]input: next_hop_idx: %d, next_mac: 0x%x:%x:%x;%x:%x:%x,  next_dip: %d.%d.%d.%d\n"
           ,param_1,*param_2,param_2[1],param_2[2],param_2[3],param_2[4],param_2[5],param_2[6],
           param_2[7],param_2[8],param_2[9]);
    if (0x1ff < param_1) goto LAB_0002d760;
    if (local_2c[0] == 0) goto LAB_0002d780;
  }
  uVar14 = pp_pm_set_indirect_cmd(0,1,param_1);
  uVar14 = uVar14 | uVar12;
  if (local_2c[0] != 0) {
LAB_0002d820:
    bVar1 = param_2[3];
    bVar2 = param_2[4];
    bVar3 = param_2[7];
    bVar4 = param_2[8];
    bVar5 = param_2[5];
    bVar6 = param_2[9];
    bVar7 = param_2[6];
    bVar8 = param_2[2];
    iVar13 = pp_pm_ind_acc_data_set(2,CONCAT11(*param_2,param_2[1]));
    iVar10 = pp_pm_ind_acc_data_set
                       (1,(uint)bVar1 << 0x10 | (uint)bVar2 << 8 | (uint)bVar5 | (uint)bVar8 << 0x18
                       );
    iVar11 = pp_pm_ind_acc_data_set
                       (0,(uint)bVar3 << 0x10 | (uint)bVar4 << 8 | (uint)bVar6 | (uint)bVar7 << 0x18
                       );
    if (((iVar13 == 0 && uVar14 == 0) && iVar10 == 0) && iVar11 == 0) {
      return 0;
    }
    if (g_tm_debug_level != 0) {
      printk("[TM][pp_pm_set_next_hop_ram_info]indirect access failed\n");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  iVar13 = 0;
  do {
    iVar13 = iVar13 + 1;
    uVar12 = pp_pm_ind_acc_done_get(local_2c);
    uVar14 = uVar14 | uVar12;
    if (local_2c[0] != 0) {
      if (iVar13 != 0x14) goto LAB_0002d820;
      break;
    }
  } while (iVar13 != 0x14);
LAB_0002d7b4:
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][pp_pm_set_next_hop_ram_info]indirect access time out\n");
  return 0xffffffff;
}

