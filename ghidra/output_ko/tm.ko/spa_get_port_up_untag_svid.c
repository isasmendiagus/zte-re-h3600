// module: tm.ko
// function: spa_get_port_up_untag_svid @ 0x3abfc
// size: 244 bytes
//

uint spa_get_port_up_untag_svid(int param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (param_1 - 1U < 7) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_get_port_up_untag_svid]input:port_id = %d\n",param_1);
    }
    iVar1 = tmOnuRegRead(0x37,&local_14,param_1 - 1U,&spaRegTable);
    if (iVar1 == 0) {
      *param_2 = local_14;
      uVar2 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][spa_get_port_up_untag_svid]output:svid = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][spa_get_port_up_untag_svid]read reg failed!\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    uVar2 = (uint)(g_tm_debug_level == 0);
    if (g_tm_debug_level != 0) {
      printk("[TM][spa_get_port_up_untag_svid]input invalid parameter!\n");
      uVar2 = 1;
    }
  }
  return uVar2;
}

