// module: switch.ko
// function: sw_port_set_port_linkmode @ 0x17b74
// size: 244 bytes
//

undefined4 sw_port_set_port_linkmode(int *param_1)

{
  code cVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar4 = param_1[1];
  cVar1 = tm_set_p2pmode[*param_1];
  iVar2 = cspplatspeed_to_sw_ztespeed((char)param_1[2]);
  uVar3 = cspplatduplex_to_sw_zteduplex((char)param_1[3]);
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n","sw_port_set_port_linkmode",
           "LinkMode.port",*param_1,"LinkMode.autoneg",param_1[1],"LinkMode.speed",param_1[2],
           "LinkMode.duplex",param_1[3]);
  }
  if (iVar2 == 2) {
    uVar4 = 1;
  }
  else {
    uVar4 = uVar4 & 0xff;
  }
  iVar2 = zte_api_sw_port_set_port_linkmode(cVar1,uVar4,iVar2,uVar3);
  uVar3 = 0;
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_set_port_linkmode",0x1cb);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

