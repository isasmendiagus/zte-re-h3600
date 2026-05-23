// module: tm.ko
// function: smac_get_tfe @ 0x30744
// size: 236 bytes
//

int smac_get_tfe(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 local_14;
  
  local_14 = 0;
  if (g_tm_debug_level < 7) {
    if (param_1 < 5) {
LAB_00030784:
      iVar1 = tmOnuRegRead(3,&local_14,param_1,&smacRegTable);
      if (iVar1 != 0) {
        if (6 < g_tm_debug_level) {
          printk("[TM][smac_get_tfe]read reg failed!\n");
          return iVar1;
        }
        return iVar1;
      }
      *param_2 = local_14;
      if (6 < g_tm_debug_level) {
        printk("[TM][smac_get_tfe]output: tfemode=%d\n");
        return 0;
      }
      return 0;
    }
  }
  else {
    printk("[TM][smac_get_tfe]input: smac=%d\n",param_1);
    if (param_1 < 5) goto LAB_00030784;
    if (6 < g_tm_debug_level) {
      printk("[TM][smac_get_tfe]input invalid parameter!\n");
    }
  }
  return 1;
}

