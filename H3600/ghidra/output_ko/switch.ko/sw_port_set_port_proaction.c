// module: switch.ko
// function: sw_port_set_port_proaction @ 0x183cc
// size: 232 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
sw_port_set_port_proaction(uint *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1 == (uint *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_port_set_port_protocolpktdeal] input ERROR: ioctl_data_sweth=null\n");
    }
  }
  else {
    uVar2 = *param_1;
    uVar4 = param_1[1];
    uVar3 = param_1[2];
    if (2 < g_switch_debug_level) {
      printk("[SW][sw_port_set_port_protocolpktdeal] input: port=%d deal=%d protocal=%d\n",uVar2,
             uVar4,uVar3,param_4);
    }
    if (_tm_port_unknwn_multicast_floodport_set <= uVar2) {
      printk("[%s]%d input port error!\n","sw_port_set_port_proaction",0x301,
             _tm_port_unknwn_multicast_floodport_set,param_4);
      return 0xffffffff;
    }
    iVar1 = tm_port_protocol_pktdeal_set(zte_api_sw_mac_set_port_macfiltermode[uVar2],uVar4,uVar3);
    if (iVar1 == 0) {
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_port_set_port_protocolpktdeal] return error: error code=0x%x\n");
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

