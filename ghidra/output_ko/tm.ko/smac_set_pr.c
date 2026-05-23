// module: tm.ko
// function: smac_set_pr @ 0x30c30
// size: 184 bytes
//

int smac_set_pr(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  if (g_tm_debug_level < 7) {
    bVar3 = param_2 != 0;
    bVar2 = param_2 == 1;
    if (param_2 < 2) {
      bVar3 = 3 < param_1;
      bVar2 = param_1 == 4;
    }
    if (!bVar3 || bVar2) {
LAB_00030c64:
      iVar1 = tmOnuRegWrite(2,param_2,param_1,&smacRegTable);
      if ((iVar1 != 0) && (6 < g_tm_debug_level)) {
        printk("[TM][smac_set_pr]write reg failed!\n");
        return iVar1;
      }
      return iVar1;
    }
  }
  else {
    printk("[TM][smac_set_pr]input: smac=%d, prmode=%d\n",param_1,param_2);
    bVar3 = param_2 != 0;
    bVar2 = param_2 == 1;
    if (param_2 < 2) {
      bVar3 = 3 < param_1;
      bVar2 = param_1 == 4;
    }
    if (!bVar3 || bVar2) goto LAB_00030c64;
    if (6 < g_tm_debug_level) {
      printk("[TM][smac_set_pr]input invalid parameter!\n");
    }
  }
  return 1;
}

