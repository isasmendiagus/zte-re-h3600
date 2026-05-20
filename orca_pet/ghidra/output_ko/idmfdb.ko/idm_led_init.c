// module: idmfdb.ko
// function: idm_led_init @ 0x127c8
// size: 160 bytes
//

undefined4 idm_led_init(void)

{
  int iVar1;
  int iVar2;
  
  __memzero(&led_handle,0x80);
  iVar1 = kallsyms_lookup_name(wifi_led_func_name);
  iVar2 = kallsyms_lookup_name(wifi_led2_func_name);
  if (iVar2 == 0 || iVar1 == 0) {
    if (iVar1 != 0) {
      register_idm_led(0,wlan_array_group_all_37893,10,iVar1);
    }
  }
  else {
    register_idm_led(0,wlan_array_group_band0_37891,6,iVar1);
    register_idm_led(1,wlan_array_group_band1_37892,6,iVar2);
  }
  return 0;
}

