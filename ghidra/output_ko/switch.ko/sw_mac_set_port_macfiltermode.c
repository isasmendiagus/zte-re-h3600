// module: switch.ko
// function: sw_mac_set_port_macfiltermode @ 0x14180
// size: 132 bytes
//

undefined4
sw_mac_set_port_macfiltermode(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  code cVar1;
  int iVar2;
  
  iVar2 = param_1[1];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input port %d mode %d\n","sw_mac_set_port_macfiltermode",cVar1,(char)iVar2,param_4)
    ;
  }
  iVar2 = zte_api_sw_mac_set_port_macfiltermode(cVar1,(char)iVar2);
  if (iVar2 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","sw_mac_set_port_macfiltermode",0x27);
  return 0xffffffff;
}

