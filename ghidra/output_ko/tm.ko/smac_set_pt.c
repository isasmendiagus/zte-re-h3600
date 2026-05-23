// module: tm.ko
// function: smac_set_pt @ 0x309d4
// size: 184 bytes
//

int smac_set_pt(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  
  if (g_tm_debug_level < 7) {
    bVar2 = 3 < param_1;
    if (param_1 < 5) {
      bVar2 = 0xffff < param_2;
    }
    if (!bVar2) {
LAB_00030a08:
      iVar1 = tmOnuRegWrite(4,param_2,param_1,&smacRegTable);
      if ((iVar1 != 0) && (6 < g_tm_debug_level)) {
        printk("[TM][smac_set_pt]write reg failed!\n");
        return iVar1;
      }
      return iVar1;
    }
  }
  else {
    printk("[TM][smac_set_pt]input: smac=%d, pt=%d\n",param_1,param_2);
    bVar2 = 3 < param_1;
    if (param_1 < 5) {
      bVar2 = 0xffff < param_2;
    }
    if (!bVar2) goto LAB_00030a08;
    if (6 < g_tm_debug_level) {
      printk("[TM][smac_set_pt]input invalid parameter!\n");
    }
  }
  return 1;
}

