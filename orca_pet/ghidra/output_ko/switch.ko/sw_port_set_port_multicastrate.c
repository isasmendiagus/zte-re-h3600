// module: switch.ko
// function: sw_port_set_port_multicastrate @ 0x19e5c
// size: 236 bytes
//

undefined4 sw_port_set_port_multicastrate(int *param_1)

{
  code cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  
  iVar4 = param_1[1];
  iVar2 = param_1[2];
  cVar1 = tm_set_p2pmode[*param_1];
  iVar6 = param_1[3];
  iVar3 = param_1[7];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %dkbps\n%s = %d\n",
           "sw_port_set_port_multicastrate","RateLimit.port",cVar1,"RateLimit.direct",(char)iVar4,
           "RateLimit.enable",(char)iVar2,"RateLimit.rate",iVar6,"RateLimit.ifgmode",(char)iVar3);
  }
  iVar4 = zte_api_sw_port_set_port_multicastrate
                    (cVar1,(char)iVar4,(char)iVar2,0,iVar6,0,(char)iVar3);
  uVar5 = 0;
  if (iVar4 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_set_port_multicastrate",0xde);
    uVar5 = 0xffffffff;
  }
  return uVar5;
}

