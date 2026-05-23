// module: tm.ko
// function: cla_set_extra_index_table @ 0x14200
// size: 544 bytes
//

undefined4 cla_set_extra_index_table(uint param_1,undefined1 *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  bool bVar6;
  int local_1c;
  
  local_1c = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_set_extra_index_table]input: \n");
    if (6 < g_tm_debug_level) {
      uVar3 = (uint)*(ushort *)(param_2 + 0x10);
      uVar4 = (uint)(byte)param_2[0x12];
      printk("index_id = %d, valid_en = %d, nomactch_cfg = %d, ext_mode = %d, index_valid = 0x%x\n",
             param_1,(uVar4 << 0x1b) >> 0x1f,(uVar4 << 0x1c) >> 0x1e,uVar4 & 1,uVar3);
      if (((g_tm_debug_level < 7) ||
          (printk("extract_index15 = %d, extract_index14 = %d, extract_index13 = %d, extract_index12 = %d\n"
                  ,param_2[0xf],param_2[0xe],param_2[0xd],param_2[0xc],uVar3), g_tm_debug_level < 7)
          ) || (printk("extract_index11 = %d, extract_index10 = %d, extract_index9 = %d, extract_index8 = %d\n"
                       ,param_2[0xb],param_2[10],param_2[9],param_2[8],uVar3), g_tm_debug_level < 7)
         ) goto LAB_0001422c;
      printk("extract_index7 = %d, extract_index6 = %d, extract_index5 = %d, extract_index4 = %d\n",
             param_2[7],param_2[6],param_2[5],param_2[4],uVar3);
    }
    if (6 < g_tm_debug_level) {
      printk("extract_index3 = %d, extract_index2 = %d, extract_index1 = %d, extract_index0 = %d\n",
             param_2[3],param_2[2],param_2[1],*param_2);
    }
  }
LAB_0001422c:
  if (param_1 < 0x10) {
    if (local_1c == 0) {
      uVar3 = 0;
      uVar4 = 0;
      do {
        uVar3 = uVar3 + 1;
        uVar1 = cla_get_indirect_rw_status(&local_1c);
        uVar4 = uVar4 | uVar1;
        bVar6 = uVar3 == 0x13;
        if (uVar3 < 0x14) {
          bVar6 = local_1c == 0;
        }
      } while (bVar6);
      if (0x13 < uVar3) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][cla_set_extra_index_table]indirect access time out\n");
        return 0xffffffff;
      }
    }
    else {
      uVar4 = 0;
    }
    puVar5 = (undefined4 *)(param_2 + 0x14);
    uVar3 = cla_set_indirect_rw_cmd(0,0,param_1);
    uVar1 = 4;
    uVar3 = uVar3 | uVar4;
    do {
      puVar5 = puVar5 + -1;
      uVar4 = cla_set_indirect_rw_data(uVar1 & 0xff,*puVar5);
      uVar1 = uVar1 - 1;
      uVar3 = uVar3 | uVar4;
    } while (uVar1 != 0xffffffff);
    if (uVar3 == 0) {
      uVar2 = 0;
    }
    else {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][cla_set_extra_index_table]indirect access failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][cla_set_extra_index_table]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}

