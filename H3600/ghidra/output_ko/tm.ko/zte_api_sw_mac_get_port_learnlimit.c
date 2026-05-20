// module: tm.ko
// function: zte_api_sw_mac_get_port_learnlimit @ 0x64b24
// size: 40 bytes
//

undefined4 zte_api_sw_mac_get_port_learnlimit(void)

{
  int iVar1;
  
  iVar1 = tm_mac_learning_limit_get();
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s]tm sdk failed!\n","zte_api_sw_mac_get_port_learnlimit");
  return 0xffffffff;
}

