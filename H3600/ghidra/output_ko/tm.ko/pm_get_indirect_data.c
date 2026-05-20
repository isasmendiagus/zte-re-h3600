// module: tm.ko
// function: pm_get_indirect_data @ 0x33508
// size: 588 bytes
//

undefined4 pm_get_indirect_data(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  int local_24 [2];
  
  uVar3 = 0;
  uVar4 = 0;
  local_24[0] = 0;
  do {
    uVar3 = uVar3 + 1;
    uVar1 = pm_get_indirect_rw_status(local_24);
    uVar4 = uVar4 | uVar1;
    bVar5 = uVar3 == 0x13;
    if (uVar3 < 0x14) {
      bVar5 = local_24[0] == 0;
    }
  } while (bVar5);
  if (uVar3 < 0x14) {
    uVar3 = pm_set_indirect_rw_cmd(1,param_1,param_2);
    uVar3 = uVar3 | uVar4;
    iVar2 = 0;
    if (local_24[0] != 0) {
LAB_00033610:
      if (param_1 == 0) {
        uVar4 = pm_get_indirect_rw_data(1,param_3 + 4);
        uVar1 = pm_get_indirect_rw_data(0,param_3);
        uVar3 = uVar3 | uVar4 | uVar1;
      }
      else if (param_1 == 1) {
        param_3 = param_3 + 0x34;
        iVar2 = 0xd;
        do {
          uVar4 = pm_get_indirect_rw_data(iVar2,param_3);
          iVar2 = iVar2 + -1;
          param_3 = param_3 + -4;
          uVar3 = uVar3 | uVar4;
        } while (iVar2 != -1);
      }
      else if (param_1 == 2) {
        param_3 = param_3 + 0x34;
        iVar2 = 0xd;
        do {
          uVar4 = pm_get_indirect_rw_data(iVar2,param_3);
          iVar2 = iVar2 + -1;
          param_3 = param_3 + -4;
          uVar3 = uVar3 | uVar4;
        } while (iVar2 != -1);
      }
      else if (param_1 == 3) {
        param_3 = param_3 + 0x34;
        iVar2 = 0xd;
        do {
          uVar4 = pm_get_indirect_rw_data(iVar2,param_3);
          iVar2 = iVar2 + -1;
          param_3 = param_3 + -4;
          uVar3 = uVar3 | uVar4;
        } while (iVar2 != -1);
      }
      else if (param_1 == 4) {
        uVar4 = pm_get_indirect_rw_data(1,param_3 + 4);
        uVar1 = pm_get_indirect_rw_data(0,param_3);
        uVar3 = uVar3 | uVar4 | uVar1;
      }
      if (uVar3 == 0) {
        return 0;
      }
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      iVar2 = ___ratelimit(_rs_7177,"pm_get_indirect_data");
      if (iVar2 == 0) {
        return 0xffffffff;
      }
      printk("[TM][pm_get_indirect_data]indirect access failed\n");
      return 0xffffffff;
    }
    do {
      iVar2 = iVar2 + 1;
      uVar4 = pm_get_indirect_rw_status(local_24);
      uVar3 = uVar3 | uVar4;
      if (local_24[0] != 0) {
        if (iVar2 != 0x14) goto LAB_00033610;
        break;
      }
    } while (iVar2 != 0x14);
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar2 = ___ratelimit(_rs_7166,"pm_get_indirect_data");
  }
  else {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar2 = ___ratelimit(_rs_7160,"pm_get_indirect_data");
  }
  if (iVar2 != 0) {
    printk("[TM][pm_get_indirect_data]indirect access time out\n");
  }
  return 0xffffffff;
}

