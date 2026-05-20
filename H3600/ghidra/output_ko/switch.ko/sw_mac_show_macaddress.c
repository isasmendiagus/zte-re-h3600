// module: switch.ko
// function: sw_mac_show_macaddress @ 0x14ae4
// size: 44 bytes
//

undefined4 sw_mac_show_macaddress(void)

{
  int iVar1;
  
  iVar1 = tm_mactable_print_get();
  if (iVar1 == 0) {
    return 0;
  }
  printk("%s %d failed!\n","sw_mac_show_macaddress",0xbd);
  return 0xffffffff;
}

