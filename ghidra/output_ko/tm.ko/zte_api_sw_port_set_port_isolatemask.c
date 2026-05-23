// module: tm.ko
// function: zte_api_sw_port_set_port_isolatemask @ 0x64a70
// size: 44 bytes
//

undefined4 zte_api_sw_port_set_port_isolatemask(void)

{
  int iVar1;
  
  iVar1 = tm_port_isolate_set();
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","zte_api_sw_port_set_port_isolatemask",0x65c);
  return 0xffffffff;
}

