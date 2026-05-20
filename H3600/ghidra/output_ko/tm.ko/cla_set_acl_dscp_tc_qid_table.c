// module: tm.ko
// function: cla_set_acl_dscp_tc_qid_table @ 0x174b4
// size: 320 bytes
//

undefined4 cla_set_acl_dscp_tc_qid_table(uint param_1,uint param_2,undefined4 *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  bool bVar7;
  int local_24 [2];
  
  local_24[0] = 0;
  if (g_tm_debug_level < 7) {
    bVar7 = 0x3e < param_2;
    bVar6 = param_2 == 0x3f;
    if (param_2 < 0x40) {
      bVar7 = 0xe < param_1;
      bVar6 = param_1 == 0xf;
    }
    if (bVar7 && !bVar6) {
LAB_000174f0:
      if (g_tm_debug_level != 0) {
        printk("[TM][cla_set_acl_dscp_tc_qid_table]input invalid parameter!\n");
      }
      return 1;
    }
  }
  else {
    printk("[TM][cla_set_acl_dscp_tc_qid_table]input: ram_index = %d, dscp = %d\n",param_1,param_2);
    bVar7 = 0x3e < param_2;
    bVar6 = param_2 == 0x3f;
    if (param_2 < 0x40) {
      bVar7 = 0xe < param_1;
      bVar6 = param_1 == 0xf;
    }
    if (bVar7 && !bVar6) goto LAB_000174f0;
    uVar5 = 0;
    if (local_24[0] != 0) goto LAB_00017558;
  }
  uVar4 = 0;
  uVar5 = 0;
  do {
    uVar4 = uVar4 + 1;
    uVar1 = cla_get_indirect_rw_status(local_24);
    uVar5 = uVar5 | uVar1;
    bVar6 = uVar4 == 0x13;
    if (uVar4 < 0x14) {
      bVar6 = local_24[0] == 0;
    }
  } while (bVar6);
  if (0x13 < uVar4) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[TM][cla_set_acl_dscp_tc_qid_table]indirect access time out\n");
    return 0xffffffff;
  }
LAB_00017558:
  iVar2 = cla_set_indirect_rw_cmd(0,9,param_2 + param_1 * 0x40);
  iVar3 = cla_set_indirect_rw_data(0,*param_3);
  if ((iVar2 != 0 || uVar5 != 0) || iVar3 != 0) {
    if (g_tm_debug_level != 0) {
      printk("[TM][cla_set_acl_dscp_tc_qid_table]indirect access failed\n");
    }
    return 0xffffffff;
  }
  return 0;
}

