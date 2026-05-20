// module: switch.ko
// function: sw_port_clear_port_count @ 0x15660
// size: 48 bytes
//

undefined4 sw_port_clear_port_count(void)

{
  int iVar1;
  
  iVar1 = zte_api_sw_port_clear_port_count();
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","sw_port_clear_port_count",0x32);
  return 0xffffffff;
}

