// module: switch.ko
// function: sw_vlan_set_port_defaultmulvlantrans @ 0x1b4f4
// size: 116 bytes
//

int sw_vlan_set_port_defaultmulvlantrans(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = *param_1;
  uVar2 = param_1[1];
  if (2 < g_switch_debug_level) {
    printk("sw_vlan_set_port_defaultmulvlantrans input:\tport=%d\taction=%d\n",uVar3,uVar2);
  }
  iVar1 = tm_port_dft_multicst_vltrans_set(uVar3,uVar2 & 0xff);
  if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
    printk("sw_vlan_set_port_defaultmulvlantrans return error!\nerror code=0x%x\n",iVar1);
  }
  return iVar1;
}

