// module: tm.ko
// function: red_set_indirect_rw_cmd @ 0x42560
// size: 232 bytes
//

undefined4 red_set_indirect_rw_cmd(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  
  if (g_tm_debug_level < 7) {
    bVar2 = 4 < param_2;
    if (param_2 < 6) {
      bVar2 = 0xffff < param_3;
    }
    if (1 < param_1) {
      bVar2 = true;
    }
    if (!bVar2) {
LAB_000425ac:
      iVar1 = tmOnuRegWrite(4,param_3 + param_2 * 0x400000 + param_1 * 0x8000000,0,RedRegTable);
      if (iVar1 == 0) {
        return 0;
      }
      if (6 < g_tm_debug_level) {
        printk("[TM][red_set_indirect_rw_cmd]reg write failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
  }
  else {
    printk("[TM][red_set_indirect_rw_cmd]input:ind_rw_en = %d, ram_id = %d, ram_addr = %d\n",param_1
           ,param_2,param_3,param_4);
    bVar2 = 4 < param_2;
    if (param_2 < 6) {
      bVar2 = 0xffff < param_3;
    }
    if (1 < param_1) {
      bVar2 = true;
    }
    if (!bVar2) goto LAB_000425ac;
    if (6 < g_tm_debug_level) {
      printk("[TM][red_set_indirect_rw_cmd]input invalid parameter!\n");
    }
  }
  return 1;
}

