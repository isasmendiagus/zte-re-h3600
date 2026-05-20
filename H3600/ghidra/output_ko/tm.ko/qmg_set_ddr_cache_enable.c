// module: tm.ko
// function: qmg_set_ddr_cache_enable @ 0x41804
// size: 224 bytes
//

int qmg_set_ddr_cache_enable(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][qmg_set_ddr_cache_enable]input: ddr_cache_en = %d\n",param_1,param_3,
           g_tm_debug_level,param_4);
  }
  if (1 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_6962,"qmg_set_ddr_cache_enable"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/tm_qmg.c",0x137);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(3,param_1,0,QmgRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_6965,"qmg_set_ddr_cache_enable"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","tm/src/tm_qmg.c",0x13f);
    return iVar1;
  }
  return iVar1;
}

