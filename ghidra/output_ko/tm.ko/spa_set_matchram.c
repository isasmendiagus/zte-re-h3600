// module: tm.ko
// function: spa_set_matchram @ 0x38120
// size: 960 bytes
//

undefined4 spa_set_matchram(byte *param_1)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  bool bVar10;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint3 local_2c;
  byte bStack_29;
  undefined4 local_28;
  undefined4 local_24;
  
  puVar8 = (undefined4 *)&stack0xffffffe0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  _local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  if ((6 < g_tm_debug_level) && (printk("[TM][spa_set_matchram]input: \n"), 6 < g_tm_debug_level)) {
    uVar6 = (uint)param_1[3];
    uVar7 = (uint)param_1[4];
    printk("rule_num = %d,  valid= %d, v4_v6_flag = %d, offset_mode = %d, offset = 0x%x\n",*param_1,
           param_1[1],param_1[2],uVar6,uVar7);
    if (6 < g_tm_debug_level) {
      printk("compare_mode = 0x%x,  mask= 0x%x, data = 0x%x\n",param_1[5],
             *(undefined2 *)(param_1 + 6),*(undefined2 *)(param_1 + 8),uVar6,uVar7);
    }
  }
  if (local_3c == 0) {
    uVar6 = 0;
    uVar7 = 0;
    do {
      uVar6 = uVar6 + 1;
      uVar5 = spa_get_indirect_rw_status(&local_3c);
      bVar10 = uVar6 == 0x13;
      if (uVar6 < 0x14) {
        bVar10 = local_3c == 0;
      }
      uVar7 = uVar7 | uVar5;
    } while (bVar10);
    if (0x13 < uVar6) {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][spa_set_matchram]indirect access time out\n");
      return 0xffffffff;
    }
  }
  else {
    uVar7 = 0;
  }
  bVar2 = *param_1;
  uVar5 = 5;
  uVar6 = spa_set_indirect_rw_cmd(1,0,bVar2 >> 2);
  uVar6 = uVar6 | uVar7;
  puVar9 = puVar8;
  do {
    puVar9 = puVar9 + -1;
    uVar7 = spa_get_indirect_rw_data(uVar5 & 0xff,puVar9);
    uVar4 = local_24;
    uVar5 = uVar5 - 1;
    uVar6 = uVar6 | uVar7;
  } while (uVar5 != 0xffffffff);
  if ((bVar2 & 3) == 0) {
    iVar1 = (param_1[5] & 3) << 7;
    uVar7 = local_28 & 0xff80007f | (uint)*(ushort *)(param_1 + 8) << 7;
    bVar3 = local_24._2_1_ & 0xf0;
    local_24._3_1_ = SUB41(uVar4,3);
    local_24._0_3_ =
         CONCAT12(bVar3 | (byte)(((uint)param_1[3] << 0x1e) >> 0x1f) | (param_1[2] & 3) << 1 |
                  (param_1[1] & 1) << 3,
                  CONCAT11((byte)((uint)iVar1 >> 8) | (param_1[4] & 0x3f) << 1 |
                           (byte)((param_1[3] & 1) << 7),param_1[7] >> 1 | (byte)iVar1));
    local_28 = CONCAT22((ushort)((uVar7 << 9) >> 0x19) | *(short *)(param_1 + 6) << 7,(short)uVar7);
  }
  else if ((bVar2 & 3) == 1) {
    _local_2c = CONCAT13((byte)(((uint)*(ushort *)(param_1 + 6) << 10) >> 0x18) |
                         (param_1[5] & 3) << 2 | (byte)((param_1[4] & 0xf) << 4),
                         (uint3)(*(ushort *)(param_1 + 8) >> 6) |
                         (uint3)((uint)*(ushort *)(param_1 + 6) << 10));
    local_28 = CONCAT31(local_28._1_3_,
                        (byte)local_28 & 0x80 | (byte)(((uint)param_1[4] << 0x1a) >> 0x1e) |
                        (param_1[3] & 3) << 2 | (param_1[2] & 3) << 4 | (param_1[1] & 1) << 6);
    local_30 = CONCAT13(local_30._3_1_ & 3 | param_1[8] << 2,(undefined3)local_30);
  }
  else if ((bVar2 & 3) == 2) {
    local_30._0_2_ =
         CONCAT11((byte)(*(ushort *)(param_1 + 6) >> 0xb) | (param_1[5] & 3) << 5,
                  (char)(*(ushort *)(param_1 + 6) >> 3));
    uVar7 = local_30 & 0xffe07fff | (param_1[4] & 0x3f) << 0xf;
    local_30._3_1_ = (byte)((local_30 & 0xffe07fff) >> 0x18);
    local_30._0_2_ = (undefined2)uVar7;
    local_30._0_3_ =
         CONCAT12((byte)(uVar7 >> 0x10) & 0x9f | (param_1[3] & 3) << 5,(undefined2)local_30);
    uVar7 = local_34 & 0xe0001fff | (uint)*(ushort *)(param_1 + 8) << 0xd;
    uVar5 = local_30 >> 0x10 & 0xfe7f | (param_1[2] & 3) << 7;
    local_30 = CONCAT22((short)uVar5,(undefined2)local_30);
    local_34 = CONCAT13((byte)((uVar7 << 3) >> 0x1b) | param_1[6] << 5,(int3)uVar7);
    local_30 = CONCAT13((byte)(uVar5 >> 8) & 0xfd | (param_1[1] & 1) << 1,(undefined3)local_30);
  }
  else {
    local_34 = CONCAT31(CONCAT21(local_34._2_2_,
                                 local_34._1_1_ & 0xe0 | param_1[3] & 3 | (param_1[2] & 3) << 2 |
                                 (param_1[1] & 1) << 4),param_1[5] & 3 | param_1[4] << 2);
    local_38 = CONCAT22(*(undefined2 *)(param_1 + 6),*(undefined2 *)(param_1 + 8));
  }
  uVar7 = spa_set_indirect_rw_cmd(0,0,bVar2 >> 2);
  uVar5 = 5;
  uVar7 = uVar7 | uVar6;
  do {
    puVar8 = puVar8 + -1;
    uVar6 = spa_set_indirect_rw_data(uVar5 & 0xff,*puVar8);
    uVar5 = uVar5 - 1;
    uVar7 = uVar7 | uVar6;
  } while (uVar5 != 0xffffffff);
  if (uVar7 != 0) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[TM][spa_set_matchram]indirect access failed\n");
    return 0xffffffff;
  }
  return 0;
}

