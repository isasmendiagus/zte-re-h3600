// module: tm.ko
// function: sbrg_set_pt_learn_mode @ 0x1908c
// size: 188 bytes
//

undefined4 sbrg_set_pt_learn_mode(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = 6 < param_2;
  bVar2 = param_2 == 7;
  if (param_2 < 8) {
    bVar3 = 2 < param_1;
    bVar2 = param_1 == 3;
  }
  if (bVar3 && !bVar2) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sbrg_set_pt_learn_mode]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sbrg_set_pt_learn_mode]input:learn_mode = %d,port_id = %d\n",param_1,param_2);
  }
  iVar1 = tmOnuRegWrite(param_2 + 0x22,param_1,0,&sbragRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sbrg_set_pt_learn_mode]write reg failed!\n");
  return 0xffffffff;
}

