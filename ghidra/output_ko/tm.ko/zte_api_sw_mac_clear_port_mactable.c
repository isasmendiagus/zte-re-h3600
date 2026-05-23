// module: tm.ko
// function: zte_api_sw_mac_clear_port_mactable @ 0x64b80
// size: 92 bytes
//

undefined4 zte_api_sw_mac_clear_port_mactable(uint param_1,uint param_2)

{
  int iVar1;
  
  if (param_2 < 4) {
    printk("cannot clear except Dynamic address\n");
    return 0;
  }
  if ((param_2 == 4) && (iVar1 = tm_port_clear_macaddr_set(1 << (param_1 & 0xff)), iVar1 != 0)) {
    printk("%s tm sdk failed!\n","zte_api_sw_mac_clear_port_mactable");
    return 0xffffffff;
  }
  return 0;
}

