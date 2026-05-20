// module: tm.ko
// function: sch_get_dn_queue_wrr_weight @ 0x40960
// size: 440 bytes
//

undefined4 sch_get_dn_queue_wrr_weight(uint param_1,uint param_2,undefined4 *param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  int local_28;
  undefined4 local_24;
  
  local_28 = 0;
  local_24 = 0;
  if (g_tm_debug_level < 7) {
    uVar1 = param_2;
    if (param_2 < 8) {
      uVar1 = param_1;
    }
    if (7 < uVar1) {
      return 1;
    }
LAB_000409a0:
    uVar2 = 0;
    do {
      uVar2 = uVar2 + 1;
      uVar1 = sch_get_ind_acc_done(&local_28);
      bVar4 = uVar2 == 0x13;
      if (uVar2 < 0x14) {
        bVar4 = local_28 == 0;
      }
    } while (bVar4);
    if (0x13 < uVar2) goto LAB_000409d0;
  }
  else {
    printk("[TM][sch_get_dn_queue_wrr_weight]input: unit = %d, queId = %d\n",param_1,param_2);
    uVar1 = param_2;
    if (param_2 < 8) {
      uVar1 = param_1;
    }
    if (7 < uVar1) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][sch_get_dn_queue_wrr_weight]input invalid parameter!\n");
      return 1;
    }
    uVar1 = 0;
    if (local_28 == 0) goto LAB_000409a0;
  }
  uVar2 = sch_set_indirect_rw_cmd(0,1,0xc,param_2 + param_1 * 8);
  if (local_28 != 0) {
    uVar2 = uVar2 | uVar1;
LAB_00040a94:
    iVar3 = sch_get_ind_acc_data(&local_24,0);
    if (iVar3 != 0 || uVar2 != 0) {
      if (g_tm_debug_level != 0) {
        printk("ERROR:(%s:%d)indirect access  write failed!\n","tm/src/pon_tm_sch.c",0xc2c);
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    *param_3 = local_24;
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_get_dn_queue_wrr_weight]output: wrrWeightVal = %d\n");
      return 0;
    }
    return 0;
  }
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    uVar2 = sch_get_ind_acc_done(&local_28);
    if (local_28 != 0) {
      if (iVar3 != 0x14) goto LAB_00040a94;
      break;
    }
  } while (iVar3 != 0x14);
LAB_000409d0:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][sch_get_dn_queue_wrr_weight]indirect access time out\n");
  return 0xffffffff;
}

