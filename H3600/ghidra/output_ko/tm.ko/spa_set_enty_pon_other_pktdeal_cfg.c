// module: tm.ko
// function: spa_set_enty_pon_other_pktdeal_cfg @ 0x3b3c8
// size: 184 bytes
//

int spa_set_enty_pon_other_pktdeal_cfg(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = 2 < param_2;
  bVar2 = param_2 == 3;
  if (param_2 < 4) {
    bVar3 = 4 < param_1;
    bVar2 = param_1 == 5;
  }
  if (bVar3 && !bVar2) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][spa_set_enty_pon_other_pktdeal_cfg]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_set_enty_pon_other_pktdeal_cfg]input:protocal_types = %d,value = %d\n",param_1,
           param_2);
  }
  iVar1 = tmOnuRegWrite(param_1 + 0x80,param_2,0,&spaRegTable);
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("[TM][spa_set_enty_pon_other_pktdeal_cfg]write reg failed!\n");
  }
  return iVar1;
}

