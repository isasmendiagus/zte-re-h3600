// module: switch.ko
// function: sw_port_set_port_enable @ 0x174ac
// size: 200 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_port_set_port_enable(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  cVar1 = (char)param_1[1];
  uVar4 = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n","sw_port_set_port_enable","PortEnable.port",uVar4,
           "PortEnable.enable",cVar1);
  }
  if (uVar4 == _tm_vlan_check_ena_set) {
    lan_up = (uint)(cVar1 != '\0');
  }
  iVar2 = zte_api_sw_port_set_port_enable(uVar4,cVar1);
  uVar3 = 0;
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_set_port_enable",0xc9);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

