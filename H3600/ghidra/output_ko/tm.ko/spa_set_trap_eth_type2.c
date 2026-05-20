// module: tm.ko
// function: spa_set_trap_eth_type2 @ 0x3a018
// size: 168 bytes
//

int spa_set_trap_eth_type2(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_set_trap_eth_type2]input: eth_type2=%x\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (0xffff < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][spa_set_trap_eth_type2]input invalid parameter!\n");
    return 1;
  }
  iVar1 = tmOnuRegWrite(0x20,param_1,0,&spaRegTable);
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("[TM][spa_set_trap_eth_type2]write reg failed!\n");
    return iVar1;
  }
  return iVar1;
}

