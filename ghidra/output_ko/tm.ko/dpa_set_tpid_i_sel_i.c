// module: tm.ko
// function: dpa_set_tpid_i_sel_i @ 0x278e8
// size: 220 bytes
//

int dpa_set_tpid_i_sel_i(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][dpa_set_tpid_i_sel_i]input:port_num = %d, tpid_id = %d, sel_id = %d, sel_val=%d\n",
           param_1,param_2,param_3,param_4);
  }
  bVar3 = 2 < param_2;
  bVar2 = param_2 == 3;
  if (param_2 < 4) {
    bVar3 = 7 < param_1;
    bVar2 = param_1 == 8;
  }
  if (!bVar3 || bVar2) {
    bVar3 = 6 < param_4;
    bVar2 = param_4 == 7;
    if (param_4 < 8) {
      bVar3 = 2 < param_3;
      bVar2 = param_3 == 3;
    }
    if (!bVar3 || bVar2) {
      iVar1 = tmOnuRegWrite(param_3 + 9 + param_2 * 4,param_4,param_1,dpaRegTable);
      if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
        printk("[TM][dpa_set_tpid_i_sel_i]write reg failed!\n");
        return iVar1;
      }
      return iVar1;
    }
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][dpa_set_tpid_i_sel_i]input invalid parameter!\n");
  }
  return 1;
}

