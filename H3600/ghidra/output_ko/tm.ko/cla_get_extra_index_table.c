// module: tm.ko
// function: cla_get_extra_index_table @ 0x14420
// size: 704 bytes
//

undefined4 cla_get_extra_index_table(uint param_1,undefined4 *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  bool bVar6;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24 [2];
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24[0] = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_get_extra_index_table]input: index_id = %d\n",param_1);
  }
  if (0xf < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][cla_get_extra_index_table]input invalid parameter!\n");
    return 1;
  }
  if (local_38 == 0) {
    uVar2 = 0;
    uVar4 = 0;
    do {
      uVar2 = uVar2 + 1;
      uVar1 = cla_get_indirect_rw_status(&local_38);
      uVar4 = uVar4 | uVar1;
      bVar6 = uVar2 == 0x13;
      if (uVar2 < 0x14) {
        bVar6 = local_38 == 0;
      }
    } while (bVar6);
    if (0x13 < uVar2) goto LAB_000144a8;
  }
  else {
    uVar4 = 0;
  }
  uVar2 = cla_set_indirect_rw_cmd(1,0,param_1);
  uVar2 = uVar2 | uVar4;
  if (local_38 != 0) {
LAB_0001452c:
    puVar5 = local_24;
    uVar4 = 4;
    do {
      uVar1 = cla_get_indirect_rw_data(uVar4 & 0xff,puVar5);
      uVar4 = uVar4 - 1;
      puVar5 = puVar5 + -1;
      uVar2 = uVar2 | uVar1;
    } while (uVar4 != 0xffffffff);
    if (uVar2 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][cla_get_extra_index_table]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    *param_2 = local_34;
    uVar4 = g_tm_debug_level;
    param_2[1] = local_30;
    param_2[2] = local_2c;
    param_2[4] = local_24[0];
    param_2[3] = local_28;
    if (6 < uVar4) {
      printk("[TM][cla_get_extra_index_table]output: \n");
      if (6 < g_tm_debug_level) {
        uVar4 = (uint)*(byte *)((int)param_2 + 0x12);
        printk("valid_en = %d, nomactch_cfg = %d, ext_mode = %d, index_valid = 0x%x\n",
               (uVar4 << 0x1b) >> 0x1f,(uVar4 << 0x1c) >> 0x1e,uVar4 & 1,
               *(undefined2 *)(param_2 + 4));
        if (g_tm_debug_level < 7) {
          return 0;
        }
        printk("extract_index15 = %d, extract_index14 = %d, extract_index13 = %d, extract_index12 = %d\n"
               ,*(undefined1 *)((int)param_2 + 0xf),*(undefined1 *)((int)param_2 + 0xe),
               *(undefined1 *)((int)param_2 + 0xd),*(undefined1 *)(param_2 + 3));
        if (g_tm_debug_level < 7) {
          return 0;
        }
        printk("extract_index11 = %d, extract_index10 = %d, extract_index9 = %d, extract_index8 = %d\n"
               ,*(undefined1 *)((int)param_2 + 0xb),*(undefined1 *)((int)param_2 + 10),
               *(undefined1 *)((int)param_2 + 9),*(undefined1 *)(param_2 + 2));
        if (g_tm_debug_level < 7) {
          return 0;
        }
        printk("extract_index7 = %d, extract_index6 = %d, extract_index5 = %d, extract_index4 = %d\n"
               ,*(undefined1 *)((int)param_2 + 7),*(undefined1 *)((int)param_2 + 6),
               *(undefined1 *)((int)param_2 + 5),*(undefined1 *)(param_2 + 1));
      }
      if (6 < g_tm_debug_level) {
        printk("extract_index3 = %d, extract_index2 = %d, extract_index1 = %d, extract_index0 = %d\n"
               ,*(undefined1 *)((int)param_2 + 3),*(undefined1 *)((int)param_2 + 2),
               *(undefined1 *)((int)param_2 + 1),*(undefined1 *)param_2);
      }
    }
    return 0;
  }
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    uVar4 = cla_get_indirect_rw_status(&local_38);
    uVar2 = uVar2 | uVar4;
    if (local_38 != 0) {
      if (iVar3 != 0x14) goto LAB_0001452c;
      break;
    }
  } while (iVar3 != 0x14);
LAB_000144a8:
  if (g_tm_debug_level != 0) {
    printk("[TM][cla_get_extra_index_table]indirect access time out\n");
  }
  return 0xffffffff;
}

