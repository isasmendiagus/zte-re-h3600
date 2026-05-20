// module: tm.ko
// function: sopc_set_smac_delay_cnt_cfg @ 0x37664
// size: 176 bytes
//

undefined4
sopc_set_smac_delay_cnt_cfg(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0xffff < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sopc_set_smac_delay_cnt_cfg]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sopc_set_smac_delay_cnt_cfg]input: delay_cnt = %d\n",param_1,param_3,
           g_tm_debug_level,param_4);
  }
  iVar1 = tmOnuRegWrite(5,param_1,0,&sopcRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sopc_set_smac_delay_cnt_cfg]reg write failed\n");
  return 0xffffffff;
}

