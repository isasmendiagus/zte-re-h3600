// module: tm.ko
// function: cla_get_cpu_queue_id @ 0x16abc
// size: 412 bytes
//

undefined4 cla_get_cpu_queue_id(uint param_1,undefined4 *param_2)

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
    if (0x3ff < param_1) {
LAB_00016af4:
      if (g_tm_debug_level != 0) {
        printk("[TM][cla_get_cpu_queue_id]input invalid parameter!\n");
      }
      return 1;
    }
LAB_00016b14:
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
    if (0x13 < uVar3) goto LAB_00016b48;
  }
  else {
    printk("[TM][cla_get_cpu_queue_id]input: ram_addr = %d\n",param_1);
    if (0x3ff < param_1) goto LAB_00016af4;
    if (local_24[0] == 0) goto LAB_00016b14;
  }
  uVar3 = cla_set_indirect_rw_cmd(1,7,param_1);
  uVar3 = uVar3 | uVar2;
  if (local_24[0] != 0) {
LAB_00016bb4:
    iVar4 = cla_get_indirect_rw_data(0,&local_28);
    if (iVar4 != 0 || uVar3 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][cla_get_cpu_queue_id]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    *param_2 = local_28;
    if (6 < g_tm_debug_level) {
      printk("[TM][cla_get_cpu_queue_id]output: cpu_qid = %d\n");
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
      if (iVar4 != 0x14) goto LAB_00016bb4;
      break;
    }
  } while (iVar4 != 0x14);
LAB_00016b48:
  if (g_tm_debug_level != 0) {
    printk("[TM][cla_get_cpu_queue_id]indirect access time out\n");
  }
  return 0xffffffff;
}

