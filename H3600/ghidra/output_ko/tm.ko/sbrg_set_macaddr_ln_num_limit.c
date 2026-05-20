// module: tm.ko
// function: sbrg_set_macaddr_ln_num_limit @ 0x196a4
// size: 188 bytes
//

undefined4 sbrg_set_macaddr_ln_num_limit(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = 6 < param_2;
  if (param_2 < 8) {
    bVar2 = 0x1fff < param_1;
  }
  if (bVar2) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sbrg_set_macaddr_ln_num_limit]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sbrg_set_macaddr_ln_num_limit]input:limit_value = %d,port_id = %d\n",param_1,
           param_2);
  }
  iVar1 = tmOnuRegWrite(0x2a,param_1,param_2,&sbragRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sbrg_set_macaddr_ln_num_limit]write reg failed!\n");
  return 0xffffffff;
}

