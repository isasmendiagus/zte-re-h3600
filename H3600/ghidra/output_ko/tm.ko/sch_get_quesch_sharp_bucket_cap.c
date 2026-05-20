// module: tm.ko
// function: sch_get_quesch_sharp_bucket_cap @ 0x3fe0c
// size: 440 bytes
//

undefined4 sch_get_quesch_sharp_bucket_cap(uint param_1,uint param_2,uint *param_3)

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
LAB_0003fe4c:
    uVar2 = 0;
    do {
      uVar2 = uVar2 + 1;
      uVar1 = sch_get_ind_acc_done(&local_28);
      bVar4 = uVar2 == 0x13;
      if (uVar2 < 0x14) {
        bVar4 = local_28 == 0;
      }
    } while (bVar4);
    if (0x13 < uVar2) goto LAB_0003fe7c;
  }
  else {
    printk("[TM][sch_get_quesch_sharp_bucket_cap]input: tcont = %d \n",param_1);
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
      printk("[TM][sch_get_quesch_sharp_bucket_cap]input invalid parameter!\n");
      return 1;
    }
    uVar1 = 0;
    if (local_28 == 0) goto LAB_0003fe4c;
  }
  uVar2 = sch_set_indirect_rw_cmd(0,1,10,param_2 + param_1 * 4);
  if (local_28 != 0) {
    uVar2 = uVar2 | uVar1;
LAB_0003ff3c:
    iVar3 = sch_get_ind_acc_data(&local_24,0);
    if (iVar3 != 0 || uVar2 != 0) {
      if (g_tm_debug_level != 0) {
        printk("ERROR:(%s:%d)indirect access  write failed!\n","tm/src/pon_tm_sch.c",0xa5c);
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    *param_3 = local_24 & 0x3fffff;
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_get_quesch_sharp_bucket_cap]output: bucketCap = %d\n");
      return 0;
    }
    return 0;
  }
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    uVar2 = sch_get_ind_acc_done(&local_28);
    if (local_28 != 0) {
      if (iVar3 != 0x14) goto LAB_0003ff3c;
      break;
    }
  } while (iVar3 != 0x14);
LAB_0003fe7c:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][sch_get_quesch_sharp_bucket_cap]indirect access time out\n");
  return 0xffffffff;
}

