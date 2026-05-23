// module: tm.ko
// function: spa_set_indirect_rw_data @ 0x37e34
// size: 176 bytes
//

undefined4 spa_set_indirect_rw_data(uint param_1,undefined4 param_2)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_set_indirect_rw_data]input: data_id = %d, rw_data = %d\n",param_1,param_2);
  }
  if (5 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][spa_set_indirect_rw_data]input invalid parameter!\n");
    return 1;
  }
  iVar1 = tmOnuRegWrite(6,param_2,param_1,&spaRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][spa_set_indirect_rw_data]reg write failed\n");
  return 0xffffffff;
}

