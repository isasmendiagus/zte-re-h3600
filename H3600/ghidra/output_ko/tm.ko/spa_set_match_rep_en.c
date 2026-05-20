// module: tm.ko
// function: spa_set_match_rep_en @ 0x390c4
// size: 172 bytes
//

int spa_set_match_rep_en(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_1 < 2) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_set_match_rep_en]input:rep_en = %d\n",param_1,param_3,g_tm_debug_level,
             param_4);
    }
    iVar1 = tmOnuRegWrite(0x13,param_1,0,&spaRegTable);
    if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
      printk("[TM][spa_set_match_rep_en]write reg failed!\n");
    }
    return iVar1;
  }
  if (g_tm_debug_level == 0) {
    return 1;
  }
  printk("[TM][spa_set_match_rep_en]input invalid parameter!\n");
  return 1;
}

