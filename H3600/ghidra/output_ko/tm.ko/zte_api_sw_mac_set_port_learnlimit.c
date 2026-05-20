// module: tm.ko
// function: zte_api_sw_mac_set_port_learnlimit @ 0x64af8
// size: 40 bytes
//

undefined4 zte_api_sw_mac_set_port_learnlimit(void)

{
  int iVar1;
  
  iVar1 = tm_mac_learning_limit_set();
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s] tm sdk failed!\n","zte_api_sw_mac_set_port_learnlimit");
  return 0xffffffff;
}

