// module: tm.ko
// function: sch_get_up_tcont_sharp_fill_rate @ 0x3eef0
// size: 420 bytes
//

undefined4 sch_get_up_tcont_sharp_fill_rate(uint param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  int local_28;
  uint local_24 [2];
  
  uVar3 = 0;
  local_28 = 0;
  local_24[0] = 0;
  if (g_tm_debug_level < 7) {
    if (0x27 < param_1) {
      return 1;
    }
LAB_0003ef28:
    uVar1 = 0;
    do {
      uVar1 = uVar1 + 1;
      uVar3 = sch_get_ind_acc_done(&local_28);
      bVar4 = uVar1 == 0x13;
      if (uVar1 < 0x14) {
        bVar4 = local_28 == 0;
      }
    } while (bVar4);
    if (0x13 < uVar1) goto LAB_0003ef58;
  }
  else {
    printk("[TM][sch_get_up_tcont_sharp_fill_rate]input: tcont%d\n",param_1);
    if (0x27 < param_1) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][sch_get_up_tcont_sharp_fill_rate]input invalid parameter!\n");
      return 1;
    }
    if (local_28 == 0) goto LAB_0003ef28;
  }
  uVar1 = sch_set_indirect_rw_cmd(0,1,5,param_1);
  if (local_28 != 0) {
    uVar1 = uVar1 | uVar3;
LAB_0003f00c:
    iVar2 = sch_get_ind_acc_data(local_24,0);
    if (iVar2 != 0 || uVar1 != 0) {
      if (g_tm_debug_level != 0) {
        printk("ERROR:(%s:%d)indirect access  write failed!\n","tm/src/pon_tm_sch.c",0x7d6);
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    *param_2 = local_24[0] & 0x1fffff;
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_get_up_tcont_sharp_fill_rate]output: fillRate = %d\n");
      return 0;
    }
    return 0;
  }
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    uVar1 = sch_get_ind_acc_done(&local_28);
    if (local_28 != 0) {
      if (iVar2 != 0x14) goto LAB_0003f00c;
      break;
    }
  } while (iVar2 != 0x14);
LAB_0003ef58:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][sch_get_up_tcont_sharp_fill_rate]indirect access time out\n");
  return 0xffffffff;
}

