// module: tm.ko
// function: cla_set_local_ipv6_addr @ 0x11a0c
// size: 176 bytes
//

undefined4 cla_set_local_ipv6_addr(uint param_1,undefined4 param_2)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_set_local_ipv6_addr]input: addr_id = %d, local_ipv6_addr = %d\n",param_1,
           param_2);
  }
  if (3 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][cla_set_local_ipv6_addr]input invalid parameter!\n");
    return 1;
  }
  iVar1 = tmOnuRegWrite(0x13,param_2,param_1,&claRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][cla_set_local_ipv6_addr]reg write failed\n");
  return 0xffffffff;
}

