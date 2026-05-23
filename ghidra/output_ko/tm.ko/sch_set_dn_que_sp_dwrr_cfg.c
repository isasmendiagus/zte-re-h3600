// module: tm.ko
// function: sch_set_dn_que_sp_dwrr_cfg @ 0x4031c
// size: 704 bytes
//

undefined4 sch_set_dn_que_sp_dwrr_cfg(uint param_1,uint param_2,uint param_3)

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
      bVar5 = 6 < param_2;
      bVar4 = param_2 == 7;
    }
    if (7 < param_1 || !bVar4 && bVar5) {
      return 1;
    }
LAB_00040388:
    uVar2 = 0;
    do {
      uVar2 = uVar2 + 1;
      uVar1 = sch_get_ind_acc_done(&local_28);
      bVar4 = uVar2 == 0x13;
      if (uVar2 < 0x14) {
        bVar4 = local_28 == 0;
      }
    } while (bVar4);
    if (0x13 < uVar2) goto LAB_000403b8;
  }
  else {
    printk("[TM][sch_set_dn_que_sp_dwrr_cfg]input: unit = %d, queId = %d, schMod = %d\n",param_1,
           param_2,param_3);
    bVar5 = param_3 != 0;
    bVar4 = param_3 == 1;
    if (param_3 < 2) {
      bVar5 = 6 < param_2;
      bVar4 = param_2 == 7;
    }
    if (7 < param_1 || bVar5 && !bVar4) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][sch_set_dn_que_sp_dwrr_cfg]input invalid parameter!\n");
      return 1;
    }
    uVar1 = 0;
    if (local_28 == 0) goto LAB_00040388;
  }
  uVar2 = sch_set_indirect_rw_cmd(0,1,0xb,param_1);
  if (local_28 == 0) {
    iVar3 = 0;
    do {
      iVar3 = iVar3 + 1;
      uVar2 = sch_get_ind_acc_done(&local_28);
      if (local_28 != 0) {
        if (iVar3 != 0x14) goto LAB_00040424;
        break;
      }
    } while (iVar3 != 0x14);
  }
  else {
    uVar2 = uVar2 | uVar1;
LAB_00040424:
    iVar3 = sch_get_ind_acc_data(&local_24,0);
    if (iVar3 != 0 || uVar2 != 0) {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("ERROR:(%s:%d)indirect access  write failed!\n","tm/src/pon_tm_sch.c",0xb34);
      return 0xffffffff;
    }
    local_24 = local_24 & ~(1 << (param_2 & 0xff)) | param_3 << (param_2 & 0xff);
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_set_dn_que_sp_dwrr_cfg] sp dwrr mask = %d\n");
    }
    uVar1 = 0;
    if (local_28 == 0) {
      iVar3 = 0;
      do {
        iVar3 = iVar3 + 1;
        uVar1 = sch_get_ind_acc_done(&local_28);
        if (local_28 != 0) {
          if (iVar3 != 0x14) goto LAB_000404c4;
          break;
        }
      } while (iVar3 != 0x14);
    }
    else {
LAB_000404c4:
      uVar2 = sch_set_indirect_rw_cmd(0,0,0xb,param_1);
      if (local_28 != 0) {
        uVar2 = uVar2 | uVar1;
LAB_00040518:
        iVar3 = sch_set_ind_acc_data(local_24,0);
        if (iVar3 == 0 && uVar2 == 0) {
          return 0;
        }
        if (g_tm_debug_level != 0) {
          printk("ERROR:(%s:%d)indirect access  write failed!\n","tm/src/pon_tm_sch.c",0xb57);
          return 0xffffffff;
        }
        return 0xffffffff;
      }
      iVar3 = 0;
      do {
        iVar3 = iVar3 + 1;
        uVar2 = sch_get_ind_acc_done(&local_28);
        if (local_28 != 0) {
          if (iVar3 != 0x14) goto LAB_00040518;
          break;
        }
      } while (iVar3 != 0x14);
    }
  }
LAB_000403b8:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][sch_set_dn_que_sp_dwrr_cfg]indirect access time out\n");
  return 0xffffffff;
}

