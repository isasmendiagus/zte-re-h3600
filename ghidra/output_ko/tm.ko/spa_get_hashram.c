// module: tm.ko
// function: spa_get_hashram @ 0x3bd94
// size: 476 bytes
//

undefined4 spa_get_hashram(uint param_1,byte *param_2)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_get_hashram]input: ram_addr = %d\n",param_1);
  }
  if (7 < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][spa_get_hashram]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  if (local_24 == 0) {
    uVar1 = 0;
    do {
      uVar1 = uVar1 + 1;
      spa_get_indirect_rw_status(&local_24);
      bVar3 = uVar1 == 0x13;
      if (uVar1 < 0x14) {
        bVar3 = local_24 == 0;
      }
    } while (bVar3);
    if (0x13 < uVar1) goto LAB_0003be04;
  }
  spa_set_indirect_rw_cmd(1,5,param_1);
  if (local_24 != 0) {
LAB_0003be80:
    spa_get_indirect_rw_data(1,&local_1c);
    iVar2 = spa_get_indirect_rw_data(0,&local_20);
    if (iVar2 == 0) {
      *(undefined4 *)param_2 = local_20;
      uVar1 = g_tm_debug_level;
      *(undefined2 *)(param_2 + 4) = (undefined2)local_1c;
      if (uVar1 < 7) {
        return 0;
      }
      printk("valid= %d, matcharray = 0x%x, action_rsn = %d, action = 0x%x\n",
             ((uint)param_2[5] << 0x1e) >> 0x1f,
             (uint)param_2[2] << 7 | (uint)(param_2[1] >> 1) | (uint)param_2[3] << 0xf |
             (uint)param_2[4] << 0x17 | (uint)param_2[5] << 0x1f,
             (param_2[1] & 1) << 6 | *param_2 >> 2,*param_2 & 3);
      return 0;
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[TM][spa_get_hashram]indirect access failed\n");
    return 0xffffffff;
  }
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    spa_get_indirect_rw_status(&local_24);
    if (local_24 != 0) {
      if (iVar2 != 0x14) goto LAB_0003be80;
      break;
    }
  } while (iVar2 != 0x14);
LAB_0003be04:
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][spa_get_hashram]indirect access time out\n");
  return 0xffffffff;
}

