// module: tm.ko
// function: pp_pm_set_indirect_cmd @ 0x2c978
// size: 216 bytes
//

undefined4 pp_pm_set_indirect_cmd(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  char cVar1;
  bool bVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_set_indirect_cmd]input: ind_rw_en = %d, ram_id = %d, ram_PP_PM_ADDR = %d\n",
           param_1,param_2,param_3,param_4);
  }
  bVar2 = 0x1e < param_2;
  if (param_2 < 0x20) {
    bVar2 = 0xfffff < param_3;
  }
  if (1 < param_1) {
    bVar2 = true;
  }
  if (bVar2) {
    if (g_tm_debug_level != 0) {
      printk("[TM][pp_pm_set_indirect_cmd]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  cVar1 = tmOnuRegWrite(0,param_3 + param_2 * 0x400000 + param_1 * 0x8000000,0,&ppPmRegTable);
  if (cVar1 == '\0') {
    return 0;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][pp_pm_set_indirect_cmd]reg write failed\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

