// module: switch.ko
// function: sw_port_get_port_flowcontrol @ 0x17774
// size: 208 bytes
//

undefined4 sw_port_get_port_flowcontrol(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  byte local_15;
  undefined4 local_14;
  
  cVar1 = tm_set_p2pmode[*param_1];
  local_15 = 0;
  local_14 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_port_get_port_flowcontrol","FlowControl.port");
  }
  iVar3 = zte_api_sw_port_get_port_flowcontrol(cVar1,&local_15,&local_14);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    param_1[1] = (uint)local_15;
    uVar4 = 0;
    if (2 < uVar2) {
      printk("[%s] output:\n%s = %d\n","sw_port_get_port_flowcontrol","FlowControl.enable");
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_flowcontrol",0x10f);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}

