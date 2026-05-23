// module: switch.ko
// function: sw_mac_clear_port_mactable @ 0x14b64
// size: 124 bytes
//

undefined4
sw_mac_clear_port_mactable(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  code cVar1;
  int iVar2;
  
  iVar2 = param_1[1];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_mac_clear_port_mactable","MacTable.port",*param_1,param_4);
  }
  iVar2 = zte_api_sw_mac_clear_port_mactable(cVar1,(char)iVar2);
  if (iVar2 == 0) {
    return 0;
  }
  printk("%s %d failed!\n","sw_mac_clear_port_mactable",0xe1);
  return 0xffffffff;
}

