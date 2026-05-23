// module: tm.ko
// function: sch_set_dn_tcont_sharp_fill_rate @ 0x40b38
// size: 400 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 sch_set_dn_tcont_sharp_fill_rate(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  int local_20 [2];
  
  local_20[0] = 0;
  local_20[1] = 0;
  if (g_tm_debug_level < 7) {
    bVar5 = 6 < param_1;
    if (param_1 < 8) {
      bVar5 = 0x1fffff < param_2;
    }
    if (bVar5) {
      return 1;
    }
LAB_00040b74:
    uVar3 = 0;
    do {
      uVar3 = uVar3 + 1;
      sch_get_ind_acc_done(local_20);
      bVar5 = uVar3 == 0x13;
      if (uVar3 < 0x14) {
        bVar5 = local_20[0] == 0;
      }
    } while (bVar5);
    if (0x13 < uVar3) goto LAB_00040ba0;
  }
  else {
    printk("[TM][sch_set_dn_tcont_sharp_fill_rate]input: unit = %d, fillRate = %d\n",param_1,param_2
          );
    bVar5 = 6 < param_1;
    if (param_1 < 8) {
      bVar5 = 0x1fffff < param_2;
    }
    if (bVar5) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][sch_set_dn_tcont_sharp_fill_rate]input invalid parameter!\n");
      return 1;
    }
    if (local_20[0] == 0) goto LAB_00040b74;
  }
  sch_set_indirect_rw_cmd(0,0,0xe,param_1);
  sch_set_ind_acc_data(param_2,0);
  iVar4 = 0;
  local_20[0] = 0;
  do {
    iVar4 = iVar4 + 1;
    iVar1 = sch_get_ind_acc_done(local_20);
    if (local_20[0] != 0) {
      if (iVar4 != 0x14) {
        iVar4 = sch_set_indirect_rw_cmd(0,1,0xe,param_1);
        iVar2 = sch_get_ind_acc_data(local_20 + 1,0);
        if ((iVar4 == 0 && iVar2 == 0) && iVar1 == 0) {
          return 0;
        }
        if (6 < g_tm_debug_level) {
          printk("[TM][sch_set_dn_tcont_sharp_fill_rate]indirect access failed\n");
          return 0xffffffff;
        }
        return 0xffffffff;
      }
      break;
    }
  } while (iVar4 != 0x14);
LAB_00040ba0:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][sch_set_dn_tcont_sharp_fill_rate]indirect access time out\n");
  return 0xffffffff;
}

