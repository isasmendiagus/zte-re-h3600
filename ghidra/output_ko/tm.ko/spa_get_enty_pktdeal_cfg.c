// module: tm.ko
// function: spa_get_enty_pktdeal_cfg @ 0x3b2c8
// size: 256 bytes
//

undefined4 spa_get_enty_pktdeal_cfg(uint param_1,uint param_2,uint *param_3)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  uint local_1c [2];
  
  bVar4 = 0x3b < param_2;
  bVar3 = param_2 == 0x3c;
  if (param_2 < 0x3d) {
    bVar4 = 6 < param_1;
    bVar3 = param_1 == 7;
  }
  local_1c[0] = 0;
  if (!bVar4 || bVar3) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_get_enty_pktdeal_cfg]input:port_id = %d,protocal_types = %d\n",param_1,
             param_2);
    }
    iVar2 = tmOnuRegRead(param_2 + 0x43,local_1c,param_1,&spaRegTable);
    if (iVar2 == 0) {
      if (local_1c[0] < 4) {
        *param_3 = local_1c[0];
      }
      if (g_tm_debug_level < 7) {
        uVar1 = 0;
      }
      else {
        printk("[TM][spa_get_enty_pktdeal_cfg]output:value = %d\n",*param_3);
        uVar1 = 0;
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][spa_get_enty_pktdeal_cfg]read reg failed!\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][spa_get_enty_pktdeal_cfg]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

