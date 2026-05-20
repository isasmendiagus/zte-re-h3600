// module: tm.ko
// function: smac_get_statistics @ 0x311fc
// size: 240 bytes
//

int smac_get_statistics(uint param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  int iVar1;
  
  if (g_tm_debug_level < 7) {
    if ((param_1 < 5) && (param_2 - 0xfU < 0x31)) {
LAB_0003123c:
      iVar1 = tmOnuRegRead(param_2,param_3,param_1,&smacRegTable);
      if (iVar1 == 0) {
        if (6 < g_tm_debug_level) {
          printk("[TM][smac_get_statistics]output: data=%d\n",*param_3);
          return 0;
        }
      }
      else if (6 < g_tm_debug_level) {
        printk("[TM][smac_get_statistics]read reg failed!\n");
        return iVar1;
      }
      return iVar1;
    }
  }
  else {
    printk("[TM][smac_get_statistics]input: smac=%d, statisticsnum=%d\n",param_1,param_2,
           g_tm_debug_level,param_4);
    if ((param_1 < 5) && (param_2 - 0xfU < 0x31)) goto LAB_0003123c;
    if (6 < g_tm_debug_level) {
      printk("[TM][smac_get_statistics]input invalid parameter!\n");
    }
  }
  return 1;
}

