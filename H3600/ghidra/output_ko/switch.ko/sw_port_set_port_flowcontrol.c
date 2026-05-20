// module: switch.ko
// function: sw_port_set_port_flowcontrol @ 0x17640
// size: 160 bytes
//

undefined4 sw_port_set_port_flowcontrol(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n","sw_port_set_port_flowcontrol","FlowControl.port",
           *param_1,"FlowControl.enable",param_1[1]);
  }
  iVar1 = zte_api_sw_port_set_port_flowcontrol
                    (zte_api_sw_mac_set_port_macfiltermode[*param_1],(char)param_1[1],0xffff);
  uVar2 = 0;
  if (iVar1 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_set_port_flowcontrol",0xf6);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

