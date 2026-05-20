// module: tm.ko
// function: spa_set_match_mode @ 0x39018
// size: 172 bytes
//

int spa_set_match_mode(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_1 < 3) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_set_match_mode]input:match_mode = %d\n",param_1,param_3,g_tm_debug_level,
             param_4);
    }
    iVar1 = tmOnuRegWrite(0x12,param_1,0,&spaRegTable);
    if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
      printk("[TM][spa_set_match_mode]write reg failed!\n");
    }
    return iVar1;
  }
  if (g_tm_debug_level == 0) {
    return 1;
  }
  printk("[TM][spa_set_match_mode]input invalid parameter!\n");
  return 1;
}

