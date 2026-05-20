// module: switch.ko
// function: sw_port_set_port_loopback @ 0x18088
// size: 180 bytes
//

int sw_port_set_port_loopback(int *param_1)

{
  code cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = param_1[1];
  uVar4 = param_1[2];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n","sw_port_set_port_loopback","LoopBack.port",
           cVar1,"LLoopBack.enable",uVar3,"LoopBack.direct",uVar4);
  }
  iVar2 = zte_api_sw_port_set_port_loopback(cVar1,uVar4 & 0xff,uVar3 & 0xff);
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_set_port_loopback",0x276);
  }
  return iVar2;
}

