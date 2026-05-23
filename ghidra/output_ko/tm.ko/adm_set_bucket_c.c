// module: tm.ko
// function: adm_set_bucket_c @ 0x2bed0
// size: 380 bytes
//

uint adm_set_bucket_c(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  int local_3c [2];
  
  local_3c[0] = 0;
  uVar5 = param_5;
  if (param_5 < 2) {
    uVar5 = param_4;
  }
  if (param_1 < 0x20 && (param_2 < 0x200000 && (param_3 < 0x10000000 && uVar5 < 2))) {
    uVar5 = 0;
    uVar6 = 0;
    do {
      uVar5 = uVar5 + 1;
      uVar1 = adm_get_ind_acc_done(local_3c);
      uVar6 = uVar6 | uVar1;
      bVar7 = uVar5 == 0x13;
      if (uVar5 < 0x14) {
        bVar7 = local_3c[0] == 0;
      }
    } while (bVar7);
    if (uVar5 < 0x14) {
      iVar2 = adm_set_indirect_rw_cmd(0,0,param_1);
      iVar3 = adm_set_ind_acc_data(1,param_2 >> 2);
      iVar4 = adm_set_ind_acc_data(0,param_3 * 4 + param_2 * 0x40000000 + param_5 + param_4 * 2);
      if (((iVar2 == 0 && iVar3 == 0) && uVar6 == 0) && iVar4 == 0) {
        return 0;
      }
      if (6 < g_tm_debug_level) {
        printk("[TM][adm_set_bucket_c]indirect access failed\n");
      }
    }
    else if (6 < g_tm_debug_level) {
      printk("[TM][adm_set_bucket_c]indirect access time out\n");
      return 0xffffffff;
    }
    uVar5 = 0xffffffff;
  }
  else {
    uVar5 = (uint)(g_tm_debug_level < 7);
    if (6 < g_tm_debug_level) {
      printk("[TM][adm_set_bucket_c]input invalid parameter!\n");
      uVar5 = 1;
    }
  }
  return uVar5;
}

