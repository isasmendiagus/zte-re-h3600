// module: switch.ko
// function: sw_port_set_port_enable @ 0x17568
// size: 156 bytes
//

undefined4 sw_port_set_port_enable(int *param_1)

{
  code cVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = param_1[1];
  cVar1 = tm_set_p2pmode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n","sw_port_set_port_enable","PortEnable.port",cVar1,
           "PortEnable.enable",(char)iVar2);
  }
  iVar2 = zte_api_sw_port_set_port_enable(cVar1,(char)iVar2);
  uVar3 = 0;
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_set_port_enable",0xcd);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

