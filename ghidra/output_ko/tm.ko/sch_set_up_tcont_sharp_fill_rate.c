// module: tm.ko
// function: sch_set_up_tcont_sharp_fill_rate @ 0x3edc0
// size: 304 bytes
//

undefined4 sch_set_up_tcont_sharp_fill_rate(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  int local_1c;
  
  local_1c = 0;
  if (g_tm_debug_level < 7) {
    bVar5 = 0x26 < param_1;
    if (param_1 < 0x28) {
      bVar5 = 0x1fffff < param_2;
    }
    if (bVar5) {
      return 1;
    }
  }
  else {
    printk("[TM][sch_set_up_tcont_sharp_fill_rate]input: tcont = %d, fillRate = %d\n",param_1,
           param_2);
    bVar5 = 0x26 < param_1;
    if (param_1 < 0x28) {
      bVar5 = 0x1fffff < param_2;
    }
    if (bVar5) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][sch_set_up_tcont_sharp_fill_rate]input invalid parameter!\n");
      return 1;
    }
    iVar1 = 0;
    if (local_1c != 0) goto LAB_0003ee94;
  }
  uVar4 = 0;
  do {
    uVar4 = uVar4 + 1;
    iVar1 = sch_get_ind_acc_done(&local_1c);
    bVar5 = uVar4 == 0x13;
    if (uVar4 < 0x14) {
      bVar5 = local_1c == 0;
    }
  } while (bVar5);
  if (0x13 < uVar4) {
    if (g_tm_debug_level < 7) {
      return 0xffffffff;
    }
    printk("[TM][sch_set_up_tcont_sharp_fill_rate]indirect access time out\n");
    return 0xffffffff;
  }
LAB_0003ee94:
  iVar2 = sch_set_indirect_rw_cmd(0,0,5,param_1);
  iVar3 = sch_set_ind_acc_data(param_2,0);
  if ((iVar2 != 0 || iVar1 != 0) || iVar3 != 0) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_set_up_tcont_sharp_fill_rate]indirect access failed\n");
    }
    return 0xffffffff;
  }
  return 0;
}

