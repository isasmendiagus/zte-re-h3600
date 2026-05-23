// module: switch.ko
// function: sw_port_get_port_802dot1xen @ 0x18784
// size: 268 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_port_get_port_802dot1xen(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 local_11;
  
  local_11 = 0;
  if (param_1 == (uint *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_port_get_port_802dot1xen] input ERROR: ioctl_data_sweth=null\n");
    }
    return 0xffffffff;
  }
  uVar3 = *param_1;
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_port_get_port_802dot1xen] input: port=%d\n",uVar3);
  }
  if (uVar3 < _tm_port_unknwn_multicast_floodport_set) {
    iVar1 = tm_port_802x_authen_get(tm_set_p2pmode[uVar3],&local_11);
    if (iVar1 == 0) {
      if (2 < g_switch_debug_level) {
        printk("[SW][sw_port_get_port_protocolpktdeal] output: enable=%d\n",local_11);
      }
      uVar2 = 0;
      *(undefined1 *)(param_1 + 1) = local_11;
    }
    else {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[SW][sw_port_get_port_protocolpktdeal] Fail: tm_port_802x_authen_get fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("[%s]%d input port error!\n","sw_port_get_port_802dot1xen",0x39d);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

