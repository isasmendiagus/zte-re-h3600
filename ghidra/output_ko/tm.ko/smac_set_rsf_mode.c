// module: tm.ko
// function: smac_set_rsf_mode @ 0x3108c
// size: 184 bytes
//

int smac_set_rsf_mode(uint param_1,uint param_2)

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
LAB_000310c0:
      iVar1 = tmOnuRegWrite(0xc,param_2,param_1,&smacRegTable);
      if ((iVar1 != 0) && (6 < g_tm_debug_level)) {
        printk("[TM][smac_set_rsf_mode]write reg failed!\n");
        return iVar1;
      }
      return iVar1;
    }
  }
  else {
    printk("[TM][smac_set_rsf_mode]input: smac=%d, dzpqmode=%d\n",param_1,param_2);
    bVar3 = param_2 != 0;
    bVar2 = param_2 == 1;
    if (param_2 < 2) {
      bVar3 = 3 < param_1;
      bVar2 = param_1 == 4;
    }
    if (!bVar3 || bVar2) goto LAB_000310c0;
    if (6 < g_tm_debug_level) {
      printk("[TM][smac_set_rsf_mode]input invalid parameter!\n");
    }
  }
  return 1;
}

