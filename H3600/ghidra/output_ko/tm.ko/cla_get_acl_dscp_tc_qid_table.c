// module: tm.ko
// function: cla_get_acl_dscp_tc_qid_table @ 0x175f4
// size: 436 bytes
//

undefined4 cla_get_acl_dscp_tc_qid_table(uint param_1,uint param_2,undefined4 *param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  bool bVar6;
  undefined4 local_20;
  int local_1c;
  
  local_20 = 0;
  local_1c = 0;
  if (g_tm_debug_level < 7) {
    bVar6 = 0x3e < param_2;
    bVar5 = param_2 == 0x3f;
    if (param_2 < 0x40) {
      bVar6 = 0xe < param_1;
      bVar5 = param_1 == 0xf;
    }
    if (bVar6 && !bVar5) {
LAB_00017634:
      if (g_tm_debug_level != 0) {
        printk("[TM][cla_get_acl_dscp_tc_qid_table]input invalid parameter!\n");
      }
      return 1;
    }
LAB_00017654:
    uVar3 = 0;
    uVar2 = 0;
    do {
      uVar3 = uVar3 + 1;
      uVar1 = cla_get_indirect_rw_status(&local_1c);
      uVar2 = uVar2 | uVar1;
      bVar5 = uVar3 == 0x13;
      if (uVar3 < 0x14) {
        bVar5 = local_1c == 0;
      }
    } while (bVar5);
    if (0x13 < uVar3) goto LAB_00017688;
  }
  else {
    printk("[TM][cla_get_acl_dscp_tc_qid_table]input: ram_index = %d,dscp = %d\n",param_1,param_2);
    bVar6 = 0x3e < param_2;
    bVar5 = param_2 == 0x3f;
    if (param_2 < 0x40) {
      bVar6 = 0xe < param_1;
      bVar5 = param_1 == 0xf;
    }
    if (bVar6 && !bVar5) goto LAB_00017634;
    uVar2 = 0;
    if (local_1c == 0) goto LAB_00017654;
  }
  uVar3 = cla_set_indirect_rw_cmd(1,9,0);
  uVar3 = uVar3 | uVar2;
  if (local_1c != 0) {
LAB_000176f4:
    iVar4 = cla_get_indirect_rw_data(0,&local_20);
    if (iVar4 != 0 || uVar3 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][cla_get_acl_dscp_tc_qid_table]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    *param_3 = local_20;
    if (6 < g_tm_debug_level) {
      printk("[TM][cla_get_acl_dscp_tc_qid_table]output: *qid = %d\n");
      return 0;
    }
    return 0;
  }
  iVar4 = 0;
  do {
    iVar4 = iVar4 + 1;
    uVar2 = cla_get_indirect_rw_status(&local_1c);
    uVar3 = uVar3 | uVar2;
    if (local_1c != 0) {
      if (iVar4 != 0x14) goto LAB_000176f4;
      break;
    }
  } while (iVar4 != 0x14);
LAB_00017688:
  if (g_tm_debug_level != 0) {
    printk("[TM][cla_get_acl_dscp_tc_qid_table]indirect access time out\n");
  }
  return 0xffffffff;
}

