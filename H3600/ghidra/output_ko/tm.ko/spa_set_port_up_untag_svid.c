// module: tm.ko
// function: spa_set_port_up_untag_svid @ 0x3ab40
// size: 188 bytes
//

int spa_set_port_up_untag_svid(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  uVar2 = param_1 - 1;
  bVar3 = 5 < uVar2;
  if (uVar2 < 7) {
    bVar3 = 0xfff < param_2;
  }
  if (!bVar3) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_set_port_up_untag_svid]input:port_id = %d,svid = %d\n",param_1,param_2);
    }
    iVar1 = tmOnuRegWrite(0x37,param_2,uVar2,&spaRegTable);
    if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
      printk("[TM][spa_set_port_up_untag_svid]write reg failed!\n");
    }
    return iVar1;
  }
  if (g_tm_debug_level == 0) {
    return 1;
  }
  printk("[TM][spa_set_port_up_untag_svid]input invalid parameter!\n");
  return 1;
}

