// module: switch.ko
// function: sw_mac_get_onu_macentrynum @ 0x14d60
// size: 200 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_mac_get_onu_macentrynum(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  int local_1c;
  
  uVar2 = 0;
  local_1c = 0;
  iVar3 = 0;
  if (_tm_port_unknwn_multicast_floodport_set != 0) {
    puVar4 = (undefined1 *)((int)&proc_create_data + 3);
    iVar3 = 0;
    do {
      puVar4 = puVar4 + 1;
      iVar1 = tm_mac_learning_number_get(*puVar4,&local_1c);
      uVar2 = uVar2 + 1;
      if (iVar1 != 0) {
        if (g_switch_debug_level != 0) {
          printk("sw_mac_get_onu_macentrynum return error!\nerror code=%x\n",iVar1);
        }
        return iVar1;
      }
      iVar3 = iVar3 + local_1c;
    } while (uVar2 < _tm_port_unknwn_multicast_floodport_set);
  }
  if (2 < g_switch_debug_level) {
    printk("sw_mac_get_onu_macentrynum output:\tlearnnum=%d\n",iVar3);
  }
  return 0;
}

