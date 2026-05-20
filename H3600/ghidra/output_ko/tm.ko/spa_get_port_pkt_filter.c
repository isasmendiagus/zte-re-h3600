// module: tm.ko
// function: spa_get_port_pkt_filter @ 0x3af58
// size: 244 bytes
//

undefined4 spa_get_port_pkt_filter(uint param_1,uint *param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint local_14;
  
  local_14 = 0;
  if (param_1 < 9) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_get_port_pkt_filter]input:port_id = %d\n",param_1);
    }
    iVar2 = tmOnuRegRead(param_1 + 0x39,&local_14,0,&spaRegTable);
    if (iVar2 == 0) {
      if (local_14 < 3) {
        *param_2 = local_14;
      }
      if (g_tm_debug_level < 7) {
        uVar1 = 0;
      }
      else {
        printk("[TM][spa_get_port_pkt_filter]output:flt_types = %d\n",*param_2);
        uVar1 = 0;
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][spa_get_port_pkt_filter]read reg failed!\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][spa_get_port_pkt_filter]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

