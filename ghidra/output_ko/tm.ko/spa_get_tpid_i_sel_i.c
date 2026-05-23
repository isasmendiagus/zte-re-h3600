// module: tm.ko
// function: spa_get_tpid_i_sel_i @ 0x3a368
// size: 280 bytes
//

int spa_get_tpid_i_sel_i(uint param_1,uint param_2,uint param_3,uint *param_4)

{
  uint uVar1;
  int iVar2;
  uint local_1c;
  
  uVar1 = param_3;
  if (param_3 < 4) {
    uVar1 = param_2;
  }
  if (param_1 < 9 && uVar1 < 4) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_get_tpid_i_sel_i]input:port_num = %d, tpid_id = %d, sel_id = %d\n",param_1,
             param_2,param_3);
    }
    iVar2 = tmOnuRegRead(param_3 + 0x22 + param_2 * 4,&local_1c,param_1,&spaRegTable);
    if (iVar2 == 0) {
      *param_4 = local_1c & 7;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][spa_get_tpid_i_sel_i]output: sel_val = %d\n");
    }
    else {
      if (g_tm_debug_level == 0) {
        return iVar2;
      }
      printk("[TM][spa_get_tpid_i_sel_i]read reg failed!\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    iVar2 = 1;
  }
  else {
    printk("[TM][spa_get_tpid_i_sel_i]input invalid parameter!\n");
    iVar2 = 1;
  }
  return iVar2;
}

