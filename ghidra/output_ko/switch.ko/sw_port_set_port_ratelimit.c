// module: switch.ko
// function: sw_port_set_port_ratelimit @ 0x198d0
// size: 256 bytes
//

int sw_port_set_port_ratelimit(int *param_1)

{
  code cVar1;
  int iVar2;
  
  iVar2 = param_1[1];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %dkbps\n%s = %d\n",
           "sw_port_set_port_ratelimit","RateLimit.port",cVar1,"RateLimit.direct",(char)iVar2,
           "RateLimit.enable",param_1[2] & 0xff,"RateLimit.rate",param_1[3],"RateLimit.ifgmode",
           (char)param_1[7]);
  }
  iVar2 = zte_api_sw_port_set_port_ratelimit(cVar1,(char)iVar2);
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_set_port_ratelimit",0x38);
  }
  return iVar2;
}

