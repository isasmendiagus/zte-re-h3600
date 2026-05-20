// module: tm.ko
// function: spa_set_color_mode @ 0x39170
// size: 244 bytes
//

int spa_set_color_mode(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  uint local_14;
  
  bVar3 = 3 < param_2;
  bVar2 = param_2 == 4;
  if (param_2 < 5) {
    bVar3 = 7 < param_1;
    bVar2 = param_1 == 8;
  }
  local_14 = 0;
  if (bVar3 && !bVar2) {
    if (g_tm_debug_level != 0) {
      printk("[TM][spa_set_color_mode]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_set_color_mode]input:port_id = %d,color_mode = %d\n",param_1,param_2);
  }
  tmOnuRegRead(0x14,&local_14,0,&spaRegTable);
  iVar1 = tmOnuRegWrite(0x14,local_14 & ~(7 << (param_1 * 3 & 0xff)) |
                             param_2 << (param_1 * 3 & 0xff),0,&spaRegTable);
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("[TM][spa_set_color_mode]write reg failed!\n");
  }
  return iVar1;
}

