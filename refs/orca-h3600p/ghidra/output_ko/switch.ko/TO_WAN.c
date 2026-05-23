// module: switch.ko
// function: TO_WAN @ 0x12328
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
    if (local_14 < 4) {
      bVar2 = _zte_api_sw_mac_set_port_learnlimit == (byte)tm_set_p2pmode[local_14];
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

