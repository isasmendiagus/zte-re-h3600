// module: tm.ko
// function: sch_get_secsch_sp_dwrr_cfg @ 0x3f7e0
// size: 476 bytes
//

undefined4 sch_get_secsch_sp_dwrr_cfg(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  int local_28;
  uint local_24;
  
  local_28 = 0;
  local_24 = 0;
  if (g_tm_debug_level < 7) {
    bVar5 = 2 < param_2;
    bVar4 = param_2 == 3;
    if (param_2 < 4) {
      bVar5 = 0x26 < param_1;
      bVar4 = param_1 == 0x27;
    }
    if (bVar5 && !bVar4) {
      return 1;
    }
LAB_0003f820:
    uVar2 = 0;
    do {
      uVar2 = uVar2 + 1;
      uVar1 = sch_get_ind_acc_done(&local_28);
      bVar4 = uVar2 == 0x13;
      if (uVar2 < 0x14) {
        bVar4 = local_28 == 0;
      }
    } while (bVar4);
    if (0x13 < uVar2) goto LAB_0003f850;
  }
  else {
    printk("[TM][sch_get_secsch_sp_dwrr_cfg]input: tcont = %d, secSchNum = %d\n",param_1,param_2);
    bVar5 = 2 < param_2;
    bVar4 = param_2 == 3;
    if (param_2 < 4) {
      bVar5 = 0x26 < param_1;
      bVar4 = param_1 == 0x27;
    }
    if (bVar5 && !bVar4) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][sch_get_secsch_sp_dwrr_cfg]input invalid parameter!\n");
      return 1;
    }
    uVar1 = 0;
    if (local_28 == 0) goto LAB_0003f820;
  }
  uVar2 = sch_set_indirect_rw_cmd(0,1,7,param_1);
  if (local_28 != 0) {
    uVar2 = uVar2 | uVar1;
LAB_0003f914:
    iVar3 = sch_get_ind_acc_data(&local_24,0);
    if (iVar3 != 0 || uVar2 != 0) {
      if (g_tm_debug_level != 0) {
        printk("ERROR:(%s:%d)indirect access  write failed!\n","tm/src/pon_tm_sch.c",0x953);
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_get_secsch_sp_dwrr_cfg] sp dwrr mask = 0x%x\n",local_24);
    }
    *param_3 = local_24 >> (param_2 & 0xff) & 1;
    if (g_tm_debug_level < 7) {
      return 0;
    }
    printk("[TM][sch_get_secsch_sp_dwrr_cfg]output: schMod = %d\n");
    return 0;
  }
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    uVar2 = sch_get_ind_acc_done(&local_28);
    if (local_28 != 0) {
      if (iVar3 != 0x14) goto LAB_0003f914;
      break;
    }
  } while (iVar3 != 0x14);
LAB_0003f850:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][sch_get_secsch_sp_dwrr_cfg]indirect access time out\n");
  return 0xffffffff;
}

