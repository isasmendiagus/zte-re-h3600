// module: tm.ko
// function: cla_set_indirect_rw_data @ 0x105b8
// size: 176 bytes
//

undefined4 cla_set_indirect_rw_data(uint param_1,undefined4 param_2)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_set_indirect_rw_data]input: data_id = %d, rw_data =0x%x\n",param_1,param_2);
  }
  if (0x10 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][cla_set_indirect_rw_data]input invalid parameter!\n");
    return 1;
  }
  iVar1 = tmOnuRegWrite(2,param_2,param_1,&claRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][cla_set_indirect_rw_data]reg write failed\n");
  return 0xffffffff;
}

