// module: tm.ko
// function: smct_set_ppmove_pmau @ 0x37404
// size: 176 bytes
//

undefined4
smct_set_ppmove_pmau(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0x3ff < param_1) {
    if (g_tm_debug_level < 7) {
      return 1;
    }
    printk("[TM][smct_set_ppmove_pmau]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][smct_set_ppmove_pmau]input:pmau = %u\n",param_1,param_3,g_tm_debug_level,param_4);
  }
  iVar1 = tmOnuRegWrite(2,param_1,0,&smctRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][smct_set_ppmove_pmau]read reg failed!\n");
  return 0xffffffff;
}

