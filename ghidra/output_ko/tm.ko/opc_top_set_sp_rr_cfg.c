// module: tm.ko
// function: opc_top_set_sp_rr_cfg @ 0x37b7c
// size: 176 bytes
//

undefined4
opc_top_set_sp_rr_cfg(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (1 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][opc_top_set_sp_rr_cfg]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][opc_top_set_sp_rr_cfg]input: sp_rr_mode = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  iVar1 = tmOnuRegWrite(8,param_1,0,&sopcRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][opc_top_set_sp_rr_cfg]reg write failed\n");
  return 0xffffffff;
}

