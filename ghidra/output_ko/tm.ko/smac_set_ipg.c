// module: tm.ko
// function: smac_set_ipg @ 0x30ce8
// size: 184 bytes
//

int smac_set_ipg(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  if (g_tm_debug_level < 7) {
    bVar3 = 6 < param_2;
    bVar2 = param_2 == 7;
    if (param_2 < 8) {
      bVar3 = 3 < param_1;
      bVar2 = param_1 == 4;
    }
    if (!bVar3 || bVar2) {
LAB_00030d1c:
      iVar1 = tmOnuRegWrite(0,param_2,param_1,&smacRegTable);
      if ((iVar1 != 0) && (6 < g_tm_debug_level)) {
        printk("[TM][smac_set_ipg]write reg failed!\n");
        return iVar1;
      }
      return iVar1;
    }
  }
  else {
    printk("[TM][smac_set_ipg]input: smac=%d, ipgmode=%d\n",param_1,param_2);
    bVar3 = 6 < param_2;
    bVar2 = param_2 == 7;
    if (param_2 < 8) {
      bVar3 = 3 < param_1;
      bVar2 = param_1 == 4;
    }
    if (!bVar3 || bVar2) goto LAB_00030d1c;
    if (6 < g_tm_debug_level) {
      printk("[TM][smac_set_ipg]input invalid parameter!\n");
    }
  }
  return 1;
}

