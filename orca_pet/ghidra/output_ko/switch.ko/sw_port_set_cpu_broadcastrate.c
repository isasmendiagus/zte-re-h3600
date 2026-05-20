// module: switch.ko
// function: sw_port_set_cpu_broadcastrate @ 0x19da0
// size: 112 bytes
//

undefined4 sw_port_set_cpu_broadcastrate(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (2 < g_switch_debug_level) {
    printk("[%s] cpu broadcast rate limit = %d\n","sw_port_set_cpu_broadcastrate",iVar1);
  }
  if (3999 < iVar1 - 1U) {
    iVar1 = 4000;
  }
  tm_protocol_pkt_limit_pps_set(0,0,1,iVar1);
  tm_protocol_pkt_limit_pps_set(1,1,1,iVar1);
  return 0;
}

