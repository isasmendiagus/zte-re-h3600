// module: tm.ko
// function: zte_api_sw_port_set_port_flowcontrol @ 0x649d8
// size: 100 bytes
//

undefined4 zte_api_sw_port_set_port_flowcontrol(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = tm_port_flow_send_ctrl_set();
  if (iVar1 != 0) {
    printk("[%s] L%d tm sdk failed!\n","zte_api_sw_port_set_port_flowcontrol",0x63d);
    return 0xffffffff;
  }
  iVar1 = tm_port_overspeed_bucket_ena_set(param_1,param_2);
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","zte_api_sw_port_set_port_flowcontrol",0x644);
  return 0xffffffff;
}

