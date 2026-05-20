// module: switch.ko
// function: sw_vlan_get_port_transparent @ 0x1b658
// size: 240 bytes
//

undefined4 sw_vlan_get_port_transparent(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 local_19 [5];
  
  local_19[0] = 0;
  if (param_1 == (int *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_vlan_get_port_transparent] input ERROR: ioctl_data_sweth=NULL\n");
    }
    return 0xffffffff;
  }
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_vlan_get_port_transparent] input: port=%d\n",cVar1);
  }
  iVar3 = tm_port_tls_get(cVar1,local_19);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    *(undefined1 *)(param_1 + 1) = local_19[0];
    uVar4 = 0;
    if (2 < uVar2) {
      printk("[SW][sw_vlan_get_port_transparent] output: port=%d enable=%d\n",cVar1);
    }
  }
  else {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][sw_vlan_get_port_transparent] return ERROR! error code=0x%x\n",iVar3);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}

