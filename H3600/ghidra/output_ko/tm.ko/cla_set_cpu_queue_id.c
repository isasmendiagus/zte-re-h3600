// module: tm.ko
// function: cla_set_cpu_queue_id @ 0x16980
// size: 316 bytes
//

undefined4 cla_set_cpu_queue_id(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  int local_1c;
  
  local_1c = 0;
  if (g_tm_debug_level < 7) {
    bVar6 = 6 < param_2;
    if (param_2 < 8) {
      bVar6 = 0x3ff < param_1;
    }
    if (bVar6) {
LAB_000169b8:
      if (g_tm_debug_level != 0) {
        printk("[TM][cla_set_cpu_queue_id]input invalid parameter!\n");
      }
      return 1;
    }
  }
  else {
    printk("[TM][cla_set_cpu_queue_id]input: ram_addr = %d, cpu_qid = %d\n",param_1,param_2);
    bVar6 = 6 < param_2;
    if (param_2 < 8) {
      bVar6 = 0x3ff < param_1;
    }
    if (bVar6) goto LAB_000169b8;
    uVar5 = 0;
    if (local_1c != 0) goto LAB_00016a20;
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
    printk("[TM][cla_set_cpu_queue_id]indirect access time out\n");
    return 0xffffffff;
  }
LAB_00016a20:
  iVar2 = cla_set_indirect_rw_cmd(0,7,param_1);
  iVar3 = cla_set_indirect_rw_data(0,param_2);
  if ((iVar2 != 0 || uVar5 != 0) || iVar3 != 0) {
    if (g_tm_debug_level != 0) {
      printk("[TM][cla_set_cpu_queue_id]indirect access failed\n");
    }
    return 0xffffffff;
  }
  return 0;
}

