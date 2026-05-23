// module: tm.ko
// function: sbrg_set_table_sel @ 0x1aca8
// size: 176 bytes
//

undefined4 sbrg_set_table_sel(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (3 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sbrg_set_table_sel]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sbrg_set_table_sel]input:ram_addr_sel = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  iVar1 = tmOnuRegWrite(0x1d,param_1,0,&sbragRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sbrg_set_table_sel]write reg failed!\n");
  return 0xffffffff;
}

