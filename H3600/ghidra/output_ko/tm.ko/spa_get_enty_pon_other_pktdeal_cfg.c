// module: tm.ko
// function: spa_get_enty_pon_other_pktdeal_cfg @ 0x3b480
// size: 244 bytes
//

undefined4 spa_get_enty_pon_other_pktdeal_cfg(uint param_1,uint *param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint local_14;
  
  local_14 = 0;
  if (param_1 < 6) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_get_enty_pon_other_pktdeal_cfg]input:protocal_types = %d\n",param_1);
    }
    iVar2 = tmOnuRegRead(param_1 + 0x80,&local_14,0,&spaRegTable);
    if (iVar2 == 0) {
      if (local_14 < 4) {
        *param_2 = local_14;
      }
      if (g_tm_debug_level < 7) {
        uVar1 = 0;
      }
      else {
        printk("[TM][spa_get_enty_pon_other_pktdeal_cfg]output:value = %d\n",*param_2);
        uVar1 = 0;
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][spa_get_enty_pon_other_pktdeal_cfg]read reg failed!\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][spa_get_enty_pon_other_pktdeal_cfg]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

