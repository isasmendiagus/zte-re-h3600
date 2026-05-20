// module: switch.ko
// function: sw_vlan_get_port_pvid @ 0x1a674
// size: 240 bytes
//

int sw_vlan_get_port_pvid(uint *param_1)

{
  int iVar1;
  uint uVar2;
  byte local_13;
  ushort local_12;
  
  local_12 = 0;
  local_13 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_vlan_get_port_pvid","Pvid.port",*param_1);
  }
  uVar2 = *param_1;
  if (1 < uVar2 - 6) {
    uVar2 = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[uVar2];
  }
  iVar1 = zte_api_sw_vlan_get_port_pvid(uVar2 & 0xff,&local_12,&local_13);
  uVar2 = g_switch_debug_level;
  if (iVar1 == 0) {
    param_1[1] = (uint)local_12;
    param_1[2] = (uint)local_13;
    if (2 < uVar2) {
      printk("[%s] output:\n%s = %d\n%s = %d\n","sw_vlan_get_port_pvid","Pvid.pvid",(uint)local_12,
             "Pvid.priority",(uint)local_13);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_vlan_get_port_pvid",0x9c);
  }
  return iVar1;
}

