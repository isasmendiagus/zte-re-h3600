// module: tm.ko
// function: spa_set_port_up_untag_pri @ 0x3acf0
// size: 188 bytes
//

int spa_set_port_up_untag_pri(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  
  uVar2 = param_1 - 1;
  bVar4 = 6 < param_2;
  bVar3 = param_2 == 7;
  if (param_2 < 8) {
    bVar4 = 5 < uVar2;
    bVar3 = uVar2 == 6;
  }
  if (!bVar4 || bVar3) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_set_port_up_untag_pri]input:port_id = %d,pri= %d\n",param_1,param_2);
    }
    iVar1 = tmOnuRegWrite(0x38,param_2,uVar2,&spaRegTable);
    if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
      printk("[TM][spa_set_port_up_untag_pri]write reg failed!\n");
    }
    return iVar1;
  }
  if (g_tm_debug_level == 0) {
    return 1;
  }
  printk("[TM][spa_set_port_up_untag_pri]input invalid parameter!\n");
  return 1;
}

