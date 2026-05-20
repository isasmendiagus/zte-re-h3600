// module: switch.ko
// function: sw_port_set_port_802dot1xen @ 0x18664
// size: 284 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
sw_port_set_port_802dot1xen(uint *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  if (param_1 == (uint *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_port_set_port_802dot1xen] input ERROR: ioctl_data_sweth=null\n");
    }
  }
  else {
    uVar3 = *param_1;
    cVar1 = (char)param_1[1];
    if (2 < g_switch_debug_level) {
      printk("[SW][sw_port_set_port_802dot1xen] input: port=%d enable=%d\n",uVar3,cVar1,
             g_switch_debug_level,param_4);
    }
    if (_tm_port_unknwn_multicast_floodport_set <= uVar3) {
      printk("[%s]%d input port error!\n","sw_port_set_port_802dot1xen",0x36a,
             _tm_port_unknwn_multicast_floodport_set,param_4);
      return 0xffffffff;
    }
    if ((cVar1 == '\x01') && (iVar2 = tm_port_status_set(tm_set_p2pmode[uVar3],0), iVar2 != 0)) {
      if (g_switch_debug_level != 0) {
        printk("[SW][sw_port_set_port_802dot1xen] Fail: tm_port_status_set fail\n");
        return 0xffffffff;
      }
    }
    else {
      iVar2 = tm_port_802x_authen_set(tm_set_p2pmode[uVar3],cVar1);
      if (iVar2 == 0) {
        return 0;
      }
      if (g_switch_debug_level != 0) {
        printk("[SW][sw_port_set_port_802dot1xen] return error: error code=0x%x\n");
        return 0xffffffff;
      }
    }
  }
  return 0xffffffff;
}

