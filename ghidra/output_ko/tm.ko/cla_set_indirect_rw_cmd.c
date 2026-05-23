// module: tm.ko
// function: cla_set_indirect_rw_cmd @ 0x1044c
// size: 212 bytes
//

undefined4 cla_set_indirect_rw_cmd(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_set_indirect_rw_cmd]input: ind_rw_en = %d, ram_id = %d, ram_addr = %d\n",
           param_1,param_2,param_3,param_4);
  }
  bVar2 = 8 < param_2;
  if (param_2 < 10) {
    bVar2 = 0x3fffff < param_3;
  }
  if (1 < param_1) {
    bVar2 = true;
  }
  if (bVar2) {
    if (g_tm_debug_level != 0) {
      printk("[TM][cla_set_indirect_rw_cmd]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(0,param_3 + param_2 * 0x400000 + param_1 * 0x8000000,0,&claRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][cla_set_indirect_rw_cmd]reg write failed\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

