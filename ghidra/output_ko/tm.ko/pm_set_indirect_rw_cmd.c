// module: tm.ko
// function: pm_set_indirect_rw_cmd @ 0x33238
// size: 252 bytes
//

undefined4 pm_set_indirect_rw_cmd(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pm_set_indirect_rw_cmd]input: ind_rw_en = %d, ram_id = %d, ram_addr = %d\n",param_1
           ,param_2,param_3,param_4);
  }
  bVar2 = 3 < param_2;
  if (param_2 < 5) {
    bVar2 = 0x3fffff < param_3;
  }
  if (1 < param_1) {
    bVar2 = true;
  }
  if (!bVar2) {
    iVar1 = tmOnuRegWrite(0,param_3 + param_2 * 0x400000 + param_1 * 0x8000000,0,pmRegTable);
    if (iVar1 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar1 = ___ratelimit(_rs_7126,"pm_set_indirect_rw_cmd"), iVar1 != 0)) {
        printk("[TM][pm_set_indirect_rw_cmd]reg write failed\n");
      }
      return 0xffffffff;
    }
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(&_rs_7123,"pm_set_indirect_rw_cmd"), iVar1 != 0)) {
    printk("[TM][pm_set_indirect_rw_cmd]input invalid parameter!\n");
  }
  return 1;
}

