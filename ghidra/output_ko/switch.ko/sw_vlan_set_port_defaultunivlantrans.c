// module: switch.ko
// function: sw_vlan_set_port_defaultunivlantrans @ 0x1acf0
// size: 172 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_vlan_set_port_defaultunivlantrans(uint *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = *param_1;
  uVar3 = param_1[1];
  if (2 < g_switch_debug_level) {
    printk("sw_vlan_set_port_defaultunivlantrans input:\tport=%d\taction=%d\n",uVar2,uVar3);
  }
  if (uVar2 < _tm_port_unknwn_multicast_floodport_set) {
    iVar1 = tm_port_dft_unkunicst_vltrans_set(zte_api_sw_mac_set_port_macfiltermode[uVar2],uVar3);
    if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
      printk("sw_vlan_set_port_defaultunivlantrans return error!\nerror code=0x%x\n",iVar1);
      return iVar1;
    }
    return iVar1;
  }
  printk("[%s]%d input port error!\n","sw_vlan_set_port_defaultunivlantrans",0x1d0);
  return -1;
}

