// module: switch.ko
// function: sw_vlan_get_port_defaultmulvlantrans @ 0x1b568
// size: 124 bytes
//

int sw_vlan_get_port_defaultmulvlantrans(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *param_1;
  iVar1 = tm_port_dft_multicst_vltrans_get(uVar2);
  if (iVar1 == 0) {
    if (2 < g_switch_debug_level) {
      printk("sw_vlan_get_port_defaultmulvlantrans output:\tport=%d\taction=%d\n",uVar2,0);
    }
  }
  else if (g_switch_debug_level != 0) {
    printk("sw_vlan_get_port_defaultmulvlantrans return error!\nerror code=0x%x\n",iVar1);
  }
  return iVar1;
}

