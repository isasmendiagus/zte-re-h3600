// module: switch.ko
// function: sw_port_get_port_multicastrate @ 0x19ebc
// size: 292 bytes
//

int sw_port_get_port_multicastrate(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  byte local_1f;
  byte local_1e;
  byte local_1d;
  int local_1c [2];
  
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  local_1f = 0;
  local_1e = 0;
  local_1c[0] = 0;
  local_1d = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_port_get_port_multicastrate","RateLimit.port",cVar1);
  }
  iVar3 = zte_api_sw_port_get_port_multicastrate(cVar1,&local_1f,&local_1e,local_1c,&local_1d);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    param_1[1] = (uint)local_1f;
    param_1[2] = (uint)local_1e;
    param_1[3] = local_1c[0];
    param_1[7] = (uint)local_1d;
    if (2 < uVar2) {
      printk("[%s] output:\n%s = %d\n%s = %d\n%s = %dkbps\n%s = %d\n",
             "sw_port_get_port_multicastrate","RateLimit.direct",(uint)local_1f,"RateLimit.enable",
             (uint)local_1e,"RateLimit.rate",local_1c[0],"RateLimit.ifgmode",(uint)local_1d);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_multicastrate",0xf6);
  }
  return iVar3;
}

