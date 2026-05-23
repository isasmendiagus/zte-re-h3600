// module: tm.ko
// function: zte_api_sw_mac_del_port_macfilterentry @ 0x64ca0
// size: 140 bytes
//

undefined4
zte_api_sw_mac_del_port_macfilterentry(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  char local_11;
  
  iVar1 = tm_mac_exchange_mode_get(&local_11);
  if (iVar1 == 0) {
    if (local_11 == '\0') {
      param_3 = 0;
    }
    iVar1 = zte_api_sw_mac_del_port_macaddress(param_1,param_2,param_3,1);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("%s %d del port mac static address failed!\n","zte_api_sw_mac_del_port_macfilterentry",
             0x9e3);
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("%s %d tm sdk failed!\n","zte_api_sw_mac_del_port_macfilterentry",0x9d4);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

