// module: tm.ko
// function: zte_api_sw_mac_clear_macaddress @ 0x64b50
// size: 44 bytes
//

undefined4 zte_api_sw_mac_clear_macaddress(void)

{
  int iVar1;
  
  iVar1 = tm_port_clear_macaddr_set(0xff);
  if (iVar1 == 0) {
    return 0;
  }
  printk("%s tm sdk failed!\n","zte_api_sw_mac_clear_macaddress");
  return 0xffffffff;
}

