// module: tm.ko
// function: spa_set_port_vlan_filter @ 0x3b04c
// size: 184 bytes
//

int spa_set_port_vlan_filter(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = 0x3e < param_2;
  bVar2 = param_2 == 0x3f;
  if (param_2 < 0x40) {
    bVar3 = 7 < param_1;
    bVar2 = param_1 == 8;
  }
  if (bVar3 && !bVar2) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][spa_set_port_vlan_filter]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_set_port_vlan_filter]input:port_id = %d,vlan_types = %d\n",param_1,param_2);
  }
  iVar1 = tmOnuRegWrite(0x42,param_2,param_1,&spaRegTable);
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("[TM][spa_set_port_vlan_filter]write reg failed!\n");
  }
  return iVar1;
}

