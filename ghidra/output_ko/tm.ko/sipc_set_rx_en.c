// module: tm.ko
// function: sipc_set_rx_en @ 0x30080
// size: 176 bytes
//

undefined4 sipc_set_rx_en(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (1 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sipc_set_rx_en]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sipc_set_rx_en]input:enable = %d\n",param_1,param_3,g_tm_debug_level,param_4);
  }
  iVar1 = tmOnuRegWrite(0,param_1,0,&sipcRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sipc_set_rx_en]write reg failed!\n");
  return 0xffffffff;
}

