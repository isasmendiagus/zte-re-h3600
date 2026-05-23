// module: tm.ko
// function: adm_set_bucket_e @ 0x2c244
// size: 324 bytes
//

uint adm_set_bucket_e(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  uint uVar8;
  uint uVar9;
  int local_24 [2];
  
  bVar7 = 0xffffffe < param_3;
  if (param_3 < 0x10000000) {
    bVar7 = 0x1fffff < param_2;
  }
  if (0x1f < param_1) {
    bVar7 = true;
  }
  local_24[0] = 0;
  if (bVar7) {
    uVar5 = (uint)(g_tm_debug_level < 7);
    if (6 < g_tm_debug_level) {
      printk("[TM][adm_set_bucket_e]input invalid parameter!\n");
      uVar5 = 1;
    }
  }
  else {
    uVar5 = 0;
    uVar6 = 0;
    uVar8 = param_2;
    uVar9 = param_3;
    do {
      uVar5 = uVar5 + 1;
      uVar1 = adm_get_ind_acc_done(local_24);
      uVar6 = uVar6 | uVar1;
      bVar7 = uVar5 == 0x13;
      if (uVar5 < 0x14) {
        bVar7 = local_24[0] == 0;
      }
    } while (bVar7);
    if (uVar5 < 0x14) {
      iVar2 = adm_set_indirect_rw_cmd(0,1,param_1,local_24[0],uVar8,uVar9);
      iVar3 = adm_set_ind_acc_data(1,param_2 >> 2);
      iVar4 = adm_set_ind_acc_data(0,param_2 * 0x40000000 + param_3 * 4);
      uVar5 = 0;
      if (((iVar2 != 0 || iVar3 != 0) || uVar6 != 0) || iVar4 != 0) {
        if (g_tm_debug_level < 7) {
          return 0xffffffff;
        }
        printk("[TM][adm_set_bucket_e]indirect access failed\n");
        return 0xffffffff;
      }
    }
    else {
      if (g_tm_debug_level < 7) {
        return 0xffffffff;
      }
      printk("[TM][adm_set_bucket_e]indirect access time out\n");
      uVar5 = 0xffffffff;
    }
  }
  return uVar5;
}

