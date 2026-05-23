// module: tm.ko
// function: spa_get_trap_protocol_type2 @ 0x39bf0
// size: 140 bytes
//

int spa_get_trap_protocol_type2(undefined4 *param_1)

{
  int iVar1;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0x1c,local_14,0,&spaRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_get_trap_protocol_type2]output: ip_type2=%x\n");
    }
  }
  else if (g_tm_debug_level != 0) {
    printk("[TM][spa_get_trap_protocol_type2]read reg failed!\n");
  }
  return iVar1;
}

