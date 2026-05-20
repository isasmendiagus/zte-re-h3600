// module: tm.ko
// function: sch_get_up_pq_sharp_bucket_cap @ 0x3ec08
// size: 440 bytes
//

undefined4 sch_get_up_pq_sharp_bucket_cap(uint param_1,uint param_2,undefined4 *param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  int local_28;
  undefined4 local_24;
  
  local_28 = 0;
  local_24 = 0;
  if (g_tm_debug_level < 7) {
    bVar5 = 6 < param_2;
    bVar4 = param_2 == 7;
    if (param_2 < 8) {
      bVar5 = 0x26 < param_1;
      bVar4 = param_1 == 0x27;
    }
    if (bVar5 && !bVar4) {
      return 1;
    }
LAB_0003ec48:
    uVar2 = 0;
    do {
      uVar2 = uVar2 + 1;
      uVar1 = sch_get_ind_acc_done(&local_28);
      bVar4 = uVar2 == 0x13;
      if (uVar2 < 0x14) {
        bVar4 = local_28 == 0;
      }
    } while (bVar4);
    if (0x13 < uVar2) goto LAB_0003ec78;
  }
  else {
    printk("[TM][sch_get_up_pq_sharp_bucket_cap]input: tcont = %d, queId = %d\n",param_1,param_2);
    bVar5 = 6 < param_2;
    bVar4 = param_2 == 7;
    if (param_2 < 8) {
      bVar5 = 0x26 < param_1;
      bVar4 = param_1 == 0x27;
    }
    if (bVar5 && !bVar4) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][sch_get_up_pq_sharp_bucket_cap]input invalid parameter!\n");
      return 1;
    }
    uVar1 = 0;
    if (local_28 == 0) goto LAB_0003ec48;
  }
  uVar2 = sch_set_indirect_rw_cmd(0,1,3,param_2 + param_1 * 8);
  if (local_28 != 0) {
    uVar2 = uVar2 | uVar1;
LAB_0003ed3c:
    iVar3 = sch_get_ind_acc_data(&local_24,0);
    if (iVar3 != 0 || uVar2 != 0) {
      if (g_tm_debug_level != 0) {
        printk("ERROR:(%s:%d)indirect access  write failed!\n","tm/src/pon_tm_sch.c",0x751);
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    *param_3 = local_24;
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_get_up_pq_sharp_bucket_cap]output: bucketCap = %d\n");
      return 0;
    }
    return 0;
  }
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    uVar2 = sch_get_ind_acc_done(&local_28);
    if (local_28 != 0) {
      if (iVar3 != 0x14) goto LAB_0003ed3c;
      break;
    }
  } while (iVar3 != 0x14);
LAB_0003ec78:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][sch_get_up_pq_sharp_bucket_cap]indirect access time out\n");
  return 0xffffffff;
}

