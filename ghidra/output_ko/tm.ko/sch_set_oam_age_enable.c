// module: tm.ko
// function: sch_set_oam_age_enable @ 0x3cf50
// size: 192 bytes
//

undefined4
sch_set_oam_age_enable(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][sch_set_oam_age_enable]input:oam_age_en = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (1 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("ERROR:(%s:%d) input invalid parameter!\n\n","tm/src/pon_tm_sch.c",0x237,g_tm_debug_level
           ,param_4);
    return 1;
  }
  iVar1 = tmOnuRegWrite(7,param_1,0,&SchRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_sch.c",0x23f,g_tm_debug_level,param_4);
  return 0xffffffff;
}

