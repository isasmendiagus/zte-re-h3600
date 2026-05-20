// module: tm.ko
// function: spa_get_port_vlan_filter @ 0x3b104
// size: 240 bytes
//

undefined4 spa_get_port_vlan_filter(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (param_1 < 9) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_get_port_vlan_filter]input:port_id = %d\n",param_1);
    }
    iVar2 = tmOnuRegRead(0x42,&local_14,param_1,&spaRegTable);
    if (iVar2 == 0) {
      *param_2 = local_14;
      uVar1 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][spa_get_port_vlan_filter]output:vlan_types = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][spa_get_port_vlan_filter]read reg failed!\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][spa_get_port_vlan_filter]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

