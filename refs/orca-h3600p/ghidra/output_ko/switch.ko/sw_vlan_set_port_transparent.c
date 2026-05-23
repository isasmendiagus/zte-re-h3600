// module: switch.ko
// function: sw_vlan_set_port_transparent @ 0x1b5e4
// size: 260 bytes
//

undefined4
sw_vlan_set_port_transparent(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  code cVar2;
  int iVar3;
  
  if (param_1 == (int *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_vlan_set_port_transparent] input ERROR: ioctl_data_sweth=NULL\n");
    }
  }
  else {
    cVar1 = (char)param_1[1];
    cVar2 = tm_set_p2pmode[*param_1];
    if (2 < g_switch_debug_level) {
      printk("[SW][sw_vlan_set_port_transparent] input: port=%d enable=%d\n",cVar2,cVar1,
             (int)&g_sw_cap + *param_1,param_4);
    }
    iVar3 = tm_port_tls_set(cVar2,cVar1);
    if (iVar3 == 0) {
      if (cVar1 != '\x01') {
        tm_vlan_check_ena_set(cVar2,0,1);
        tm_vlan_check_ena_set(cVar2,1,1);
        return 0;
      }
      tm_vlan_check_ena_set(cVar2,0,0);
      tm_vlan_check_ena_set(cVar2,1,0);
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_vlan_set_port_transparent] return ERROR! error code=0x%x\n",iVar3);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

