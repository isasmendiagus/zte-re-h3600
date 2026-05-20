// module: switch.ko
// function: sw_vlan_set_port_pvid @ 0x1a5ac
// size: 196 bytes
//

int sw_vlan_set_port_pvid(uint *param_1)

{
  uint *puVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  
  puVar3 = param_1;
  if (2 < g_switch_debug_level) {
    puVar3 = (uint *)printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n","sw_vlan_set_port_pvid",
                            "Pvid.port",*param_1,"Pvid.pvid",param_1[1],"Pvid.priority",param_1[2]);
  }
  uVar5 = *param_1;
  uVar4 = uVar5 - 6;
  puVar1 = (uint *)uVar5;
  if (1 < uVar4) {
    uVar5 = (int)&g_sw_cap + uVar5;
    puVar1 = puVar3;
  }
  if (1 < uVar4) {
    puVar1 = (uint *)(uint)*(byte *)(uVar5 + 0xc);
  }
  iVar2 = zte_api_sw_vlan_set_port_pvid((uint)puVar1 & 0xff,(short)param_1[1],(char)param_1[2]);
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_vlan_set_port_pvid",0x7d);
  }
  return iVar2;
}

