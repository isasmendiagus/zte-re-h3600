// module: tm.ko
// function: sch_set_secsch_sp_dwrr_cfg @ 0x3f520
// size: 704 bytes
//

undefined4 sch_set_secsch_sp_dwrr_cfg(uint param_1,uint param_2,uint param_3)

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
    bVar5 = param_3 != 0;
    bVar4 = param_3 == 1;
    if (param_3 < 2) {
      bVar5 = 2 < param_2;
      bVar4 = param_2 == 3;
    }
    if (0x27 < param_1 || !bVar4 && bVar5) {
      return 1;
    }
LAB_0003f58c:
    uVar2 = 0;
    do {
      uVar2 = uVar2 + 1;
      uVar1 = sch_get_ind_acc_done(&local_28);
      bVar4 = uVar2 == 0x13;
      if (uVar2 < 0x14) {
        bVar4 = local_28 == 0;
      }
    } while (bVar4);
    if (0x13 < uVar2) goto LAB_0003f5bc;
  }
  else {
    printk("[TM][sch_set_secsch_sp_dwrr_cfg]input: tcont = %d, SecSchNum = %d, SchMod = %d\n",
           param_1,param_2,param_3);
    bVar5 = param_3 != 0;
    bVar4 = param_3 == 1;
    if (param_3 < 2) {
      bVar5 = 2 < param_2;
      bVar4 = param_2 == 3;
    }
    if (0x27 < param_1 || bVar5 && !bVar4) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][sch_set_secsch_sp_dwrr_cfg]input invalid parameter!\n");
      return 1;
    }
    uVar1 = 0;
    if (local_28 == 0) goto LAB_0003f58c;
  }
  uVar2 = sch_set_indirect_rw_cmd(0,1,7,param_1);
  if (local_28 == 0) {
    iVar3 = 0;
    do {
      iVar3 = iVar3 + 1;
      uVar2 = sch_get_ind_acc_done(&local_28);
      if (local_28 != 0) {
        if (iVar3 != 0x14) goto LAB_0003f628;
        break;
      }
    } while (iVar3 != 0x14);
  }
  else {
    uVar2 = uVar2 | uVar1;
LAB_0003f628:
    iVar3 = sch_get_ind_acc_data(&local_24,0);
    if (iVar3 != 0 || uVar2 != 0) {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("ERROR:(%s:%d)indirect access  write failed!\n","tm/src/pon_tm_sch.c",0x8ed);
      return 0xffffffff;
    }
    local_24 = local_24 & ~(1 << (param_2 & 0xff)) | param_3 << (param_2 & 0xff);
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_set_secsch_sp_dwrr_cfg] sp dwrr mask = 0x%x\n");
    }
    uVar1 = 0;
    if (local_28 == 0) {
      iVar3 = 0;
      do {
        iVar3 = iVar3 + 1;
        uVar1 = sch_get_ind_acc_done(&local_28);
        if (local_28 != 0) {
          if (iVar3 != 0x14) goto LAB_0003f6c8;
          break;
        }
      } while (iVar3 != 0x14);
    }
    else {
LAB_0003f6c8:
      uVar2 = sch_set_indirect_rw_cmd(0,0,7,param_1);
      if (local_28 != 0) {
        uVar2 = uVar2 | uVar1;
LAB_0003f71c:
        iVar3 = sch_set_ind_acc_data(local_24,0);
        if (iVar3 == 0 && uVar2 == 0) {
          return 0;
        }
        if (g_tm_debug_level != 0) {
          printk("ERROR:(%s:%d)indirect access  write failed!\n","tm/src/pon_tm_sch.c",0x90f);
          return 0xffffffff;
        }
        return 0xffffffff;
      }
      iVar3 = 0;
      do {
        iVar3 = iVar3 + 1;
        uVar2 = sch_get_ind_acc_done(&local_28);
        if (local_28 != 0) {
          if (iVar3 != 0x14) goto LAB_0003f71c;
          break;
        }
      } while (iVar3 != 0x14);
    }
  }
LAB_0003f5bc:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][sch_set_secsch_sp_dwrr_cfg]indirect access time out\n");
  return 0xffffffff;
}

