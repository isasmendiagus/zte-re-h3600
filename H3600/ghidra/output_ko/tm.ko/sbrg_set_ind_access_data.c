// module: tm.ko
// function: sbrg_set_ind_access_data @ 0x19360
// size: 184 bytes
//

undefined4 sbrg_set_ind_access_data(undefined4 param_1,uint param_2)

{
  int iVar1;
  
  if (2 < param_2) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sbrg_set_ind_access_data]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sbrg_set_ind_access_data]input:data = %d,data_map = %d\n",param_1,param_2);
  }
  iVar1 = tmOnuRegWrite(0x16,param_1,param_2,&sbragRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sbrg_set_ind_access_data]write reg failed!\n");
  return 0xffffffff;
}

