// module: switch.ko
// function: sw_set_wanport_qos @ 0x1326c
// size: 48 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sw_set_wanport_qos(void)

{
  uint *puVar1;
  
  puVar1 = (uint *)(_zte_api_sw_mac_set_port_learnlimit * 0x14 + -0xbe2bce8);
  *puVar1 = *puVar1 & 0xfffcffff;
  return;
}

