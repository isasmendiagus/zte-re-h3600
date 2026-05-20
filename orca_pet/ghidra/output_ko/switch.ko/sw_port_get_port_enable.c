// module: switch.ko
// function: sw_port_get_port_enable @ 0x17608
// size: 196 bytes
//

undefined4 sw_port_get_port_enable(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  byte local_11;
  
  cVar1 = tm_set_p2pmode[*param_1];
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_port_get_port_enable","PortEnable.port",cVar1);
  }
  iVar3 = zte_api_sw_port_get_port_enable(cVar1,&local_11);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    param_1[1] = (uint)local_11;
    uVar4 = 0;
    if (2 < uVar2) {
      printk("[%s] output:\nPortEnable.enable = %d\n","sw_port_get_port_enable");
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_enable",0xe2);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}

