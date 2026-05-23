// module: tm.ko
// function: cla_get_acl_aging_table @ 0x17318
// size: 412 bytes
//

undefined4 cla_get_acl_aging_table(uint param_1,undefined4 *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  undefined4 local_28;
  int local_24 [2];
  
  uVar2 = 0;
  local_28 = 0;
  local_24[0] = 0;
  if (g_tm_debug_level < 7) {
    if (0x103ff < param_1) {
LAB_00017350:
      if (g_tm_debug_level != 0) {
        printk("[TM][cla_get_acl_aging_table]input invalid parameter!\n");
      }
      return 1;
    }
LAB_00017370:
    uVar3 = 0;
    uVar2 = 0;
    do {
      uVar3 = uVar3 + 1;
      uVar1 = cla_get_indirect_rw_status(local_24);
      uVar2 = uVar2 | uVar1;
      bVar5 = uVar3 == 0x13;
      if (uVar3 < 0x14) {
        bVar5 = local_24[0] == 0;
      }
    } while (bVar5);
    if (0x13 < uVar3) goto LAB_000173a4;
  }
  else {
    printk("[TM][cla_get_acl_aging_table]input: ram_addr = %d\n",param_1);
    if (0x103ff < param_1) goto LAB_00017350;
    if (local_24[0] == 0) goto LAB_00017370;
  }
  uVar3 = cla_set_indirect_rw_cmd(1,8,param_1);
  uVar3 = uVar3 | uVar2;
  if (local_24[0] != 0) {
LAB_00017410:
    iVar4 = cla_get_indirect_rw_data(0,&local_28);
    if (iVar4 != 0 || uVar3 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][cla_get_acl_aging_table]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    *param_2 = local_28;
    if (6 < g_tm_debug_level) {
      printk("[TM][cla_get_acl_aging_table]output: cpu_qid = %d\n");
      return 0;
    }
    return 0;
  }
  iVar4 = 0;
  do {
    iVar4 = iVar4 + 1;
    uVar2 = cla_get_indirect_rw_status(local_24);
    uVar3 = uVar3 | uVar2;
    if (local_24[0] != 0) {
      if (iVar4 != 0x14) goto LAB_00017410;
      break;
    }
  } while (iVar4 != 0x14);
LAB_000173a4:
  if (g_tm_debug_level != 0) {
    printk("[TM][cla_get_acl_aging_table]indirect access time out\n");
  }
  return 0xffffffff;
}

