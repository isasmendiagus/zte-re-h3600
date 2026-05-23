// module: switch.ko
// function: sw_mac_clear_macaddress @ 0x14bc8
// size: 44 bytes
//

undefined4 sw_mac_clear_macaddress(void)

{
  int iVar1;
  
  iVar1 = zte_api_sw_mac_clear_macaddress();
  if (iVar1 == 0) {
    return 0;
  }
  printk("%s %d failed!\n","sw_mac_clear_macaddress",0xc9);
  return 0xffffffff;
}

