// module: tm.ko
// function: spa_get_port_dft_pri @ 0x38f34
// size: 228 bytes
//

undefined4 spa_get_port_dft_pri(uint param_1,undefined4 *param_2)

{
  int iVar1;
  
  if (7 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][spa_get_port_dft_pri]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_get_port_dft_pri]input:port_id = %d\n",param_1);
  }
  iVar1 = tmOnuRegRead(param_1 + 10,param_2,0,&spaRegTable);
  if (iVar1 != 0) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[TM][spa_get_port_dft_pri]read reg failed!\n");
    return 0xffffffff;
  }
  *param_2 = 0;
  if (g_tm_debug_level < 7) {
    return 0;
  }
  printk("[TM][spa_get_port_dft_pri]output:value = %d\n",0);
  return 0;
}

