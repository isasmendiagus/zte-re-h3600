// module: tm.ko
// function: spa_set_trap_eth_type1 @ 0x39ee4
// size: 168 bytes
//

int spa_set_trap_eth_type1(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_set_trap_eth_type1]input: eth_type1=%x\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (0xffff < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][spa_set_trap_eth_type1]input invalid parameter!\n");
    return 1;
  }
  iVar1 = tmOnuRegWrite(0x1f,param_1,0,&spaRegTable);
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("[TM][spa_set_trap_eth_type1]write reg failed!\n");
    return iVar1;
  }
  return iVar1;
}

