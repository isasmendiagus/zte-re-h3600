// module: switch.ko
// function: sw_port_get_port_proaction @ 0x18548
// size: 280 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_port_get_port_proaction(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (param_1 == (uint *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_port_get_port_protocolpktdeal] input ERROR: ioctl_data_sweth=null\n");
    }
    return 0xffffffff;
  }
  uVar3 = *param_1;
  uVar4 = param_1[2];
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_port_get_port_protocolpktdeal] input: port=%d protocal=%d\n",uVar3,uVar4);
  }
  if (uVar3 < _tm_port_unknwn_multicast_floodport_set) {
    iVar1 = tm_port_protocol_pktdeal_get(tm_set_p2pmode[uVar3],local_1c,uVar4);
    if (iVar1 == 0) {
      if (2 < g_switch_debug_level) {
        printk("[SW][sw_port_get_port_protocolpktdeal] output: deal=%d\n",local_1c[0]);
      }
      uVar2 = 0;
      param_1[1] = local_1c[0];
    }
    else {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[SW][sw_port_get_port_protocolpktdeal] return error: error code=0x%x\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("[%s]%d input port error!\n","sw_port_get_port_proaction",0x33f);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

