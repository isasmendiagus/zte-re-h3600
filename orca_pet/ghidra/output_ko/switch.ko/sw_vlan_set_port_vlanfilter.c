// module: switch.ko
// function: sw_vlan_set_port_vlanfilter @ 0x1b7d8
// size: 184 bytes
//

undefined4 sw_vlan_set_port_vlanfilter(int *param_1)

{
  code cVar1;
  int iVar2;
  
  if (param_1 == (int *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("sw_vlan_set_port_vlanfilter input ERROR!\nioctl_data_sweth=NULL\n");
    }
  }
  else {
    iVar2 = param_1[1];
    cVar1 = tm_set_p2pmode[*param_1];
    if (2 < g_switch_debug_level) {
      printk("sw_vlan_set_port_vlanfilter input:\nport=%d\nvlan_mask=%d\n",cVar1,iVar2);
    }
    iVar2 = tm_port_vlan_filter_set(cVar1,iVar2);
    if (iVar2 == 0) {
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("sw_vlan_set_port_vlanfilter return ERROR!\nerror code=0x%x\n");
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

