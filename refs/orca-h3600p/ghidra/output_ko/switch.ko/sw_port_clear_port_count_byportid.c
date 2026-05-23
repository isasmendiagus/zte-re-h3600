// module: switch.ko
// function: sw_port_clear_port_count_byportid @ 0x15744
// size: 64 bytes
//

undefined4 sw_port_clear_port_count_byportid(int *param_1)

{
  int iVar1;
  
  iVar1 = zte_api_sw_port_clear_count_by_portid(tm_set_p2pmode[*param_1]);
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","sw_port_clear_port_count_byportid",0x41);
  return 0xffffffff;
}

