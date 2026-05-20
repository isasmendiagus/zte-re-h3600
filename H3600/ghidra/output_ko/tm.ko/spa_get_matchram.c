// module: tm.ko
// function: spa_get_matchram @ 0x3b948
// size: 1052 bytes
//

undefined4 spa_get_matchram(uint param_1,undefined4 *param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  bool bVar7;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_get_matchram]input: ram_addr = %d\n",param_1);
  }
  if (7 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][spa_get_matchram]input invalid parameter!\n");
    return 1;
  }
  if (local_3c == 0) {
    uVar3 = 0;
    uVar5 = 0;
    do {
      uVar3 = uVar3 + 1;
      uVar2 = spa_get_indirect_rw_status(&local_3c);
      bVar7 = uVar3 == 0x13;
      if (uVar3 < 0x14) {
        bVar7 = local_3c == 0;
      }
      uVar5 = uVar5 | uVar2;
    } while (bVar7);
    if (0x13 < uVar3) goto LAB_0003b9d4;
  }
  else {
    uVar5 = 0;
  }
  uVar3 = spa_set_indirect_rw_cmd(1,0,param_1);
  uVar3 = uVar3 | uVar5;
  if (local_3c == 0) {
    iVar4 = 0;
    do {
      iVar4 = iVar4 + 1;
      uVar5 = spa_get_indirect_rw_status(&local_3c);
      uVar3 = uVar3 | uVar5;
      if (local_3c != 0) {
        if (iVar4 != 0x14) goto LAB_0003ba58;
        break;
      }
    } while (iVar4 != 0x14);
LAB_0003b9d4:
    if (g_tm_debug_level != 0) {
      printk("[TM][spa_get_matchram]indirect access time out\n");
    }
    return 0xffffffff;
  }
LAB_0003ba58:
  puVar6 = &local_24;
  uVar5 = 5;
  do {
    uVar2 = spa_get_indirect_rw_data(uVar5 & 0xff,puVar6);
    uVar5 = uVar5 - 1;
    puVar6 = puVar6 + -1;
    uVar3 = uVar3 | uVar2;
  } while (uVar5 != 0xffffffff);
  if (uVar3 != 0) {
    if (g_tm_debug_level != 0) {
      printk("[TM][spa_get_matchram]indirect access failed\n");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  *param_2 = local_38;
  uVar5 = g_tm_debug_level;
  param_2[1] = local_34;
  param_2[2] = local_30;
  param_2[3] = local_2c;
  param_2[4] = local_28;
  *(undefined2 *)(param_2 + 5) = (undefined2)local_24;
  *(undefined1 *)((int)param_2 + 0x16) = local_24._2_1_;
  if (uVar5 < 7) {
    return 0;
  }
  printk("[TM][spa_get_matchram]output: \n");
  if (6 < g_tm_debug_level) {
    uVar5 = (uint)*(byte *)((int)param_2 + 0x16);
    uVar3 = ((uint)*(byte *)((int)param_2 + 0x15) << 0x19) >> 0x1a;
    printk("valid0= %d, v4_v6_flag0 = %d, offset_mode0 = %d, offset0 = 0x%x\n",
           (uVar5 << 0x1c) >> 0x1f,(uVar5 << 0x1d) >> 0x1e,
           (uVar5 & 1) << 1 | (uint)(*(byte *)((int)param_2 + 0x15) >> 7),uVar3);
    if (g_tm_debug_level < 7) {
      return 0;
    }
    printk("compare_mode = 0x%x,  mask= 0x%x, data = 0x%x\n",
           (*(byte *)((int)param_2 + 0x15) & 1) << 1 | *(byte *)(param_2 + 5) >> 7,
           (uint)*(byte *)((int)param_2 + 0x13) << 1 | (uint)(*(byte *)((int)param_2 + 0x12) >> 7) |
           (*(byte *)(param_2 + 5) & 0x7f) << 9,
           (uint)*(byte *)((int)param_2 + 0x11) << 1 | (uint)(*(byte *)(param_2 + 4) >> 7) |
           (*(byte *)((int)param_2 + 0x12) & 0x7f) << 9,uVar3);
    if (g_tm_debug_level < 7) goto LAB_0003bcfc;
    uVar5 = (uint)*(byte *)(param_2 + 4);
    uVar3 = (uVar5 & 3) << 4 | (uint)(*(byte *)((int)param_2 + 0xf) >> 4);
    printk("valid1= %d, v4_v6_flag1 = %d, offset_mode1 = %d, offset1 = 0x%x\n",
           (uVar5 << 0x19) >> 0x1f,(uVar5 << 0x1a) >> 0x1e,(uVar5 << 0x1c) >> 0x1e,uVar3);
    if (g_tm_debug_level < 7) {
      return 0;
    }
    printk("compare_mode1 = 0x%x,  mask1= 0x%x, data1 = 0x%x\n",
           ((uint)*(byte *)((int)param_2 + 0xf) << 0x1c) >> 0x1e,
           (uint)*(byte *)((int)param_2 + 0xe) << 6 | (uint)(*(byte *)((int)param_2 + 0xd) >> 2) |
           (*(byte *)((int)param_2 + 0xf) & 3) << 0xe,
           (uint)*(byte *)(param_2 + 3) << 6 | (uint)(*(byte *)((int)param_2 + 0xb) >> 2) |
           (*(byte *)((int)param_2 + 0xd) & 3) << 0xe,uVar3);
  }
  if (g_tm_debug_level < 7) {
    return 0;
  }
  bVar1 = *(byte *)((int)param_2 + 10);
  uVar5 = (bVar1 & 0x1f) << 1 | (uint)(*(byte *)((int)param_2 + 9) >> 7);
  printk("valid2= %d, v4_v6_flag2 = %d, offset_mode2 = %d, offset2 = 0x%x\n",
         ((uint)*(byte *)((int)param_2 + 0xb) << 0x1e) >> 0x1f,
         (*(byte *)((int)param_2 + 0xb) & 1) << 1 | (uint)(bVar1 >> 7),((uint)bVar1 << 0x19) >> 0x1e
         ,uVar5);
  if (g_tm_debug_level < 7) {
    return 0;
  }
  printk("compare_mode2 = 0x%x,  mask2= 0x%x, data2 = 0x%x\n",
         ((uint)*(byte *)((int)param_2 + 9) << 0x19) >> 0x1e,
         (uint)*(byte *)(param_2 + 2) << 3 | (uint)(*(byte *)((int)param_2 + 7) >> 5) |
         (*(byte *)((int)param_2 + 9) & 0x1f) << 0xb,
         (uint)*(byte *)((int)param_2 + 6) << 3 | (uint)(*(byte *)((int)param_2 + 5) >> 5) |
         (*(byte *)((int)param_2 + 7) & 0x1f) << 0xb,uVar5);
LAB_0003bcfc:
  if (6 < g_tm_debug_level) {
    uVar3 = (uint)*(byte *)((int)param_2 + 5);
    uVar5 = (uint)(*(byte *)(param_2 + 1) >> 2);
    printk("valid3= %d, v4_v6_flag3 = %d, offset_mode3 = %d, offset3 = 0x%x\n",
           (uVar3 << 0x1b) >> 0x1f,(uVar3 << 0x1c) >> 0x1e,uVar3 & 3,uVar5);
    if (6 < g_tm_debug_level) {
      printk("compare_mode3 = 0x%x,  mask3= 0x%x, data3 = 0x%x\n",*(byte *)(param_2 + 1) & 3,
             *(undefined2 *)((int)param_2 + 2),*(undefined2 *)param_2,uVar5);
    }
  }
  return 0;
}

