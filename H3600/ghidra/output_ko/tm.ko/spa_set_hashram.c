// module: tm.ko
// function: spa_set_hashram @ 0x37ee4
// size: 340 bytes
//

undefined4 spa_set_hashram(undefined4 param_1,byte *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  int local_1c;
  
  local_1c = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_set_hashram]input: \n");
    if (6 < g_tm_debug_level) {
      printk("valid= %d, matcharray = 0x%x, action_rsn = %d, action = 0x%x\n",
             ((uint)param_2[5] << 0x1e) >> 0x1f,
             (uint)param_2[2] << 7 | (uint)(param_2[1] >> 1) | (uint)param_2[3] << 0xf |
             (uint)param_2[4] << 0x17 | (uint)param_2[5] << 0x1f,
             (param_2[1] & 1) << 6 | *param_2 >> 2,*param_2 & 3);
    }
    if (local_1c != 0) {
      uVar6 = 0;
      goto LAB_00037fd0;
    }
  }
  uVar5 = 0;
  uVar6 = 0;
  do {
    uVar5 = uVar5 + 1;
    uVar1 = spa_get_indirect_rw_status(&local_1c);
    bVar7 = uVar5 == 0x13;
    if (uVar5 < 0x14) {
      bVar7 = local_1c == 0;
    }
    uVar6 = uVar6 | uVar1;
  } while (bVar7);
  if (0x13 < uVar5) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[TM][spa_set_matchram]indirect access time out\n");
    return 0xffffffff;
  }
LAB_00037fd0:
  iVar2 = spa_set_indirect_rw_cmd(0,5,param_1);
  iVar3 = spa_set_indirect_rw_data(1,*(undefined4 *)(param_2 + 4));
  iVar4 = spa_set_indirect_rw_data(0,*(undefined4 *)param_2);
  if (((iVar2 != 0 || uVar6 != 0) || iVar3 != 0) || iVar4 != 0) {
    if (g_tm_debug_level != 0) {
      printk("[TM][spa_set_matchram]indirect access failed\n");
    }
    return 0xffffffff;
  }
  return 0;
}

