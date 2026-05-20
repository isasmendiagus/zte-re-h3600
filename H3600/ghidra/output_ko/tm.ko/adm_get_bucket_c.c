// module: tm.ko
// function: adm_get_bucket_c @ 0x2c04c
// size: 496 bytes
//

undefined4 adm_get_bucket_c(uint param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  int local_2c;
  uint local_28;
  uint local_24 [2];
  
  uVar3 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24[0] = 0;
  if (g_tm_debug_level < 7) {
    if (0x1f < param_1) {
      return 1;
    }
LAB_0002c088:
    uVar4 = 0;
    uVar3 = 0;
    do {
      uVar4 = uVar4 + 1;
      uVar1 = adm_get_ind_acc_done(&local_2c);
      uVar3 = uVar3 | uVar1;
      bVar6 = uVar4 == 0x13;
      if (uVar4 < 0x14) {
        bVar6 = local_2c == 0;
      }
    } while (bVar6);
    if (0x13 < uVar4) goto LAB_0002c0bc;
  }
  else {
    printk("[TM][adm_get_bucket_c]input: Unit = %d\n",param_1);
    if (0x1f < param_1) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][adm_get_bucket_c]input invalid parameter!\n");
      return 1;
    }
    if (local_2c == 0) goto LAB_0002c088;
  }
  uVar4 = adm_set_indirect_rw_cmd(1,0,param_1);
  uVar4 = uVar4 | uVar3;
  if (local_2c != 0) {
LAB_0002c170:
    iVar5 = adm_get_ind_acc_data(1,local_24);
    iVar2 = adm_get_ind_acc_data(0,&local_28);
    if ((iVar5 == 0 && uVar4 == 0) && iVar2 == 0) {
      *param_2 = (local_24[0] & 0x1ffff) * 4 + (local_28 >> 0x1e);
      uVar3 = g_tm_debug_level;
      param_2[2] = (local_28 << 0x1e) >> 0x1f;
      param_2[3] = local_28 & 1;
      param_2[1] = (local_28 << 2) >> 4;
      if (6 < uVar3) {
        printk("[TM][adm_get_bucket_c]output: bucket_en = %d, coup_en = %d, cir = %d, cbs = %d\n");
        return 0;
      }
      return 0;
    }
    if (g_tm_debug_level != 0) {
      iVar5 = ___ratelimit(_rs_7336,"adm_get_bucket_c");
      if (iVar5 != 0) {
        printk("ERROR:(%s:%d)indirect access  write failed!\n","pp_adm.c",0x599);
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  iVar5 = 0;
  do {
    iVar5 = iVar5 + 1;
    uVar3 = adm_get_ind_acc_done(&local_2c);
    uVar4 = uVar4 | uVar3;
    if (local_2c != 0) {
      if (iVar5 != 0x14) goto LAB_0002c170;
      break;
    }
  } while (iVar5 != 0x14);
LAB_0002c0bc:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][adm_get_bucket_c]indirect access time out\n");
  return 0xffffffff;
}

