// module: tm.ko
// function: sch_set_up_queue_wrr_weight @ 0x3e414
// size: 468 bytes
//

undefined4 sch_set_up_queue_wrr_weight(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  int local_24;
  
  local_24 = 0;
  if (g_tm_debug_level < 7) {
    bVar4 = 6 < param_2;
    if (param_2 < 8) {
      bVar4 = 0x3ffff < param_3;
    }
    if (0x27 < param_1) {
      bVar4 = true;
    }
    if (bVar4) {
      return 1;
    }
LAB_0003e464:
    uVar2 = 0;
    do {
      uVar2 = uVar2 + 1;
      uVar1 = sch_get_ind_acc_done(&local_24);
      bVar4 = uVar2 == 0x13;
      if (uVar2 < 0x14) {
        bVar4 = local_24 == 0;
      }
    } while (bVar4);
    if (0x13 < uVar2) goto LAB_0003e494;
  }
  else {
    printk("[TM][sch_set_up_queue_wrr_weight]input: tcont = %d, queId = %d, wrrWeightVal = %d\n",
           param_1,param_2,param_3);
    bVar4 = 6 < param_2;
    if (param_2 < 8) {
      bVar4 = 0x3ffff < param_3;
    }
    if (0x27 < param_1) {
      bVar4 = true;
    }
    if (bVar4) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][sch_set_up_queue_wrr_weight]input invalid parameter!\n");
      return 1;
    }
    uVar1 = 0;
    if (local_24 == 0) goto LAB_0003e464;
  }
  uVar2 = sch_set_indirect_rw_cmd(0,0,1,param_2 + param_1 * 8);
  if (local_24 != 0) {
    uVar2 = uVar2 | uVar1;
LAB_0003e568:
    printk("\n---wrrWeightVal=%d",param_3);
    iVar3 = sch_set_ind_acc_data(param_3,0);
    if (iVar3 != 0 || uVar2 != 0) {
      if (6 < g_tm_debug_level) {
        printk("[TM][sch_set_up_queue_wrr_weight]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_set_up_queue_wrr_weight] cfg wrrWeightVal = %d\n",param_3);
      return 0;
    }
    return 0;
  }
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    uVar2 = sch_get_ind_acc_done(&local_24);
    if (local_24 != 0) {
      if (iVar3 != 0x14) goto LAB_0003e568;
      break;
    }
  } while (iVar3 != 0x14);
LAB_0003e494:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][sch_set_up_queue_wrr_weight]indirect access time out\n");
  return 0xffffffff;
}

