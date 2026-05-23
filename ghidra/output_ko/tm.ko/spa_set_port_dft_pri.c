// module: tm.ko
// function: spa_set_port_dft_pri @ 0x38e7c
// size: 184 bytes
//

int spa_set_port_dft_pri(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = param_2;
  if (param_2 < 8) {
    uVar1 = param_1;
  }
  if (7 < uVar1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][spa_set_port_dft_pri]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_set_port_dft_pri]input:port_id = %d,value = %d\n",param_1,param_2);
  }
  iVar2 = tmOnuRegWrite(param_1 + 10,param_2,0,&spaRegTable);
  if ((iVar2 != 0) && (g_tm_debug_level != 0)) {
    printk("[TM][spa_set_port_dft_pri]write reg failed!\n");
  }
  return iVar2;
}

