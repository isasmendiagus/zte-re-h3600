// module: tm.ko
// function: spa_set_enty_pktdeal_cfg @ 0x3b1f4
// size: 212 bytes
//

int spa_set_enty_pktdeal_cfg(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = 2 < param_3;
  bVar2 = param_3 == 3;
  if (param_3 < 4) {
    bVar3 = 0x3b < param_2;
    bVar2 = param_2 == 0x3c;
  }
  if (7 < param_1 || bVar3 && !bVar2) {
    if (g_tm_debug_level != 0) {
      printk("[TM][spa_set_enty_pktdeal_cfg]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_set_enty_pktdeal_cfg]input:port_id = %d,protocal_types = %d,value = %d\n",
           param_1,param_2,param_3,param_4);
  }
  iVar1 = tmOnuRegWrite(param_2 + 0x43,param_3,param_1,&spaRegTable);
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("[TM][spa_set_enty_pktdeal_cfg]write reg failed!\n");
  }
  return iVar1;
}

