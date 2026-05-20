// module: switch.ko
// function: sw_vlan_set_port_inframemode @ 0x1a374
// size: 160 bytes
//

int sw_vlan_set_port_inframemode(int *param_1)

{
  code cVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = param_1[1];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n","sw_vlan_set_port_inframemode","InframeMode.port",
           *param_1,"InframeMode.mode",uVar3);
  }
  iVar2 = zte_api_sw_vlan_set_port_inframemode(cVar1,uVar3 & 0xff);
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed![zte_api_sw_vlan_set_port_inframemode]\n",
           "sw_vlan_set_port_inframemode",0x2d);
  }
  return iVar2;
}

