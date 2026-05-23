// module: switch.ko
// function: TO_WAN @ 0x124c4
// size: 280 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool TO_WAN(char *param_1)

{
  int iVar1;
  bool bVar2;
  uint local_14;
  
  local_14 = 0;
  if (2 < g_switch_debug_level) {
    printk("dev name %s\n",param_1);
  }
  iVar1 = strncmp(param_1,"pon",3);
  if ((iVar1 == 0) || (iVar1 = strncmp(param_1,"ptm",3), iVar1 == 0)) {
    bVar2 = true;
  }
  else {
    iVar1 = strncmp(param_1,"eth",3);
    if (iVar1 != 0) {
      return false;
    }
    sscanf(param_1,"eth%u",&local_14);
    if (local_14 < 5) {
      bVar2 = _tm_vlan_check_ena_set == (byte)zte_api_sw_mac_set_port_macfiltermode[local_14];
    }
    else {
      if (g_switch_debug_level == 0) {
        return false;
      }
      printk("[%s] name=%s, wrong port=%d\n","TO_WAN",param_1);
      bVar2 = false;
    }
  }
  return bVar2;
}

