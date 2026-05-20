// module: tm.ko
// function: spa_set_cpu_untag_svid @ 0x3a708
// size: 172 bytes
//

int spa_set_cpu_untag_svid(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_1 < 0x1000) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_set_cpu_untag_svid]input:svid = %d\n",param_1,param_3,g_tm_debug_level,
             param_4);
    }
    iVar1 = tmOnuRegWrite(0x34,param_1,0,&spaRegTable);
    if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
      printk("[TM][spa_set_cpu_untag_svid]write reg failed!\n");
    }
    return iVar1;
  }
  if (g_tm_debug_level == 0) {
    return 1;
  }
  printk("[TM][spa_set_cpu_untag_svid]input invalid parameter!\n");
  return 1;
}

