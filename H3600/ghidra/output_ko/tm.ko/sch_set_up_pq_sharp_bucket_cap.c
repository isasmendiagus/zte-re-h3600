// module: tm.ko
// function: sch_set_up_pq_sharp_bucket_cap @ 0x3eab0
// size: 344 bytes
//

undefined4 sch_set_up_pq_sharp_bucket_cap(uint param_1,uint param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  int local_24 [2];
  
  local_24[0] = 0;
  if (g_tm_debug_level < 7) {
    bVar5 = 6 < param_2;
    if (param_2 < 8) {
      bVar5 = 0x3fffff < param_3;
    }
    if (0x27 < param_1) {
      bVar5 = true;
    }
    if (bVar5) {
      return 1;
    }
  }
  else {
    printk("[TM][sch_set_up_pq_sharp_bucket_cap]input: tcont = %d, queId = %d, bucketCap = %d\n",
           param_1,param_2,param_3);
    bVar5 = 6 < param_2;
    if (param_2 < 8) {
      bVar5 = 0x3fffff < param_3;
    }
    if (0x27 < param_1) {
      bVar5 = true;
    }
    if (bVar5) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][sch_set_up_pq_sharp_bucket_cap]input invalid parameter!\n");
      return 1;
    }
    iVar1 = 0;
    if (local_24[0] != 0) goto LAB_0003ebac;
  }
  uVar4 = 0;
  do {
    uVar4 = uVar4 + 1;
    iVar1 = sch_get_ind_acc_done(local_24);
    bVar5 = uVar4 == 0x13;
    if (uVar4 < 0x14) {
      bVar5 = local_24[0] == 0;
    }
  } while (bVar5);
  if (0x13 < uVar4) {
    if (g_tm_debug_level < 7) {
      return 0xffffffff;
    }
    printk("[TM][sch_set_up_pq_sharp_bucket_cap]indirect access time out\n");
    return 0xffffffff;
  }
LAB_0003ebac:
  iVar2 = sch_set_indirect_rw_cmd(0,0,3,param_2 + param_1 * 8);
  iVar3 = sch_set_ind_acc_data(param_3,0);
  if ((iVar2 != 0 || iVar1 != 0) || iVar3 != 0) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_set_up_pq_sharp_bucket_cap]indirect access failed\n");
    }
    return 0xffffffff;
  }
  return 0;
}

