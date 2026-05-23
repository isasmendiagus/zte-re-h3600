// module: tm.ko
// function: cla_get_local_ipv6_addr @ 0x11abc
// size: 232 bytes
//

undefined4 cla_get_local_ipv6_addr(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_get_local_ipv6_addr]input: addr_id = %d\n",param_1);
  }
  if (param_1 < 4) {
    iVar2 = tmOnuRegRead(0x13,&local_14,param_1,&claRegTable);
    if (iVar2 == 0) {
      *param_2 = local_14;
      uVar1 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][cla_get_local_ipv6_addr]output: local_ipv6_addr = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][cla_get_local_ipv6_addr]reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][cla_get_local_ipv6_addr]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

