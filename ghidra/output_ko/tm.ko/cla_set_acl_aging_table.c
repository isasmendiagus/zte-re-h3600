// module: tm.ko
// function: cla_set_acl_aging_table @ 0x171cc
// size: 332 bytes
//

undefined4 cla_set_acl_aging_table(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  bool bVar7;
  int local_1c;
  
  local_1c = 0;
  if (g_tm_debug_level < 7) {
    bVar7 = param_2 != 0;
    bVar6 = param_2 == 1;
    if (param_2 < 2) {
      bVar7 = 0x103fd < param_1;
      bVar6 = param_1 == 0x103fe;
    }
    if (bVar7 && !bVar6) {
LAB_0001720c:
      if (g_tm_debug_level != 0) {
        printk("[TM][cla_set_acl_aging_table]input invalid parameter!\n");
      }
      return 1;
    }
  }
  else {
    printk("[TM][cla_set_acl_aging_table]input: ram_addr = %d, age_en = %d\n",param_1,param_2);
    bVar7 = param_2 != 0;
    bVar6 = param_2 == 1;
    if (param_2 < 2) {
      bVar7 = 0x103fd < param_1;
      bVar6 = param_1 == 0x103fe;
    }
    if (bVar7 && !bVar6) goto LAB_0001720c;
    uVar5 = 0;
    if (local_1c != 0) goto LAB_00017274;
  }
  uVar4 = 0;
  uVar5 = 0;
  do {
    uVar4 = uVar4 + 1;
    uVar1 = cla_get_indirect_rw_status(&local_1c);
    uVar5 = uVar5 | uVar1;
    bVar6 = uVar4 == 0x13;
    if (uVar4 < 0x14) {
      bVar6 = local_1c == 0;
    }
  } while (bVar6);
  if (0x13 < uVar4) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[TM][cla_set_acl_aging_table]indirect access time out\n");
    return 0xffffffff;
  }
LAB_00017274:
  iVar2 = cla_set_indirect_rw_cmd(0,8,param_1);
  iVar3 = cla_set_indirect_rw_data(0,param_2);
  if ((iVar2 != 0 || uVar5 != 0) || iVar3 != 0) {
    if (g_tm_debug_level != 0) {
      printk("[TM][cla_set_acl_aging_table]indirect access failed\n");
    }
    return 0xffffffff;
  }
  return 0;
}

