// module: tm.ko
// function: spa_set_stp_action @ 0x389f0
// size: 172 bytes
//

int spa_set_stp_action(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_1 < 4) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_set_stp_action]input:action = %d\n",param_1,param_3,g_tm_debug_level,param_4)
      ;
    }
    iVar1 = tmOnuRegWrite(7,param_1,0,&spaRegTable);
    if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
      printk("[TM][spa_set_stp_action]write reg failed!\n");
    }
    return iVar1;
  }
  if (g_tm_debug_level == 0) {
    return 1;
  }
  printk("[TM][spa_set_stp_action]input invalid parameter!\n");
  return 1;
}

