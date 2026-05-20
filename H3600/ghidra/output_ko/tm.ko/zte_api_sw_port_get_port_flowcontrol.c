// module: tm.ko
// function: zte_api_sw_port_get_port_flowcontrol @ 0x64a40
// size: 44 bytes
//

undefined4 zte_api_sw_port_get_port_flowcontrol(void)

{
  int iVar1;
  
  iVar1 = tm_port_flow_send_ctrl_get();
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","zte_api_sw_port_get_port_flowcontrol",0x650);
  return 0xffffffff;
}

