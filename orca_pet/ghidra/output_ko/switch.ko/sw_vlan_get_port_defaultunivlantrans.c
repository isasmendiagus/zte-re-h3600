// module: switch.ko
// function: sw_vlan_get_port_defaultunivlantrans @ 0x1ae30
// size: 184 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_vlan_get_port_defaultunivlantrans(uint *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 local_14 [2];
  
  uVar2 = *param_1;
  local_14[0] = 0;
  if (uVar2 < _tm_port_unknwn_multicast_floodport_set) {
    iVar1 = tm_port_dft_unkunicst_vltrans_get(tm_set_p2pmode[uVar2],local_14);
    if (iVar1 == 0) {
      if (2 < g_switch_debug_level) {
        printk("sw_vlan_get_port_defaultunivlantrans output:\tport=%d\taction=%d\n",uVar2,
               local_14[0]);
      }
    }
    else if (g_switch_debug_level != 0) {
      printk("sw_vlan_get_port_defaultunivlantrans return error!\nerror code=0x%x\n",iVar1);
    }
  }
  else {
    printk("[%s]%d input port error!\n","sw_vlan_get_port_defaultunivlantrans",0x1f1);
    iVar1 = -1;
  }
  return iVar1;
}

