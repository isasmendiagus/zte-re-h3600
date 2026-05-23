// module: switch.ko
// function: sw_vlan_get_port_vlanfilter @ 0x1b800
// size: 236 bytes
//

undefined4 sw_vlan_get_port_vlanfilter(int *param_1)

{
  code cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_14;
  
  local_14 = 0;
  if (param_1 == (int *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("sw_vlan_get_port_vlanfilter input ERROR!\nioctl_data_sweth=NULL\n");
    }
    return 0xffffffff;
  }
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("sw_vlan_get_port_vlanfilter input:\nport=%d\n",cVar1);
  }
  iVar2 = tm_port_vlan_filter_get(cVar1,&local_14);
  if (iVar2 == 0) {
    uVar3 = 0;
    if (2 < g_switch_debug_level) {
      printk("sw_vlan_get_port_vlanfilter output:\tport=%d\tvlan_mask=%d\n",cVar1,local_14);
    }
  }
  else {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("sw_vlan_get_port_vlanfilter return ERROR!\nerror code=0x%x\n",iVar2);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

