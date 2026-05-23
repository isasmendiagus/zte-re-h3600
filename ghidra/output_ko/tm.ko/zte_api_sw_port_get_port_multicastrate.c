// module: tm.ko
// function: zte_api_sw_port_get_port_multicastrate @ 0x6340c
// size: 172 bytes
//

undefined4
zte_api_sw_port_get_port_multicastrate
          (uint param_1,undefined1 *param_2,undefined1 *param_3,undefined4 *param_4,
          undefined4 param_5)

{
  undefined4 uVar1;
  char local_1d;
  int local_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  
  if (param_1 < 8) {
    tm_port_cast_rate_limit_get(param_1,&local_1d,&local_18,2);
    if (local_1d != '\0') {
      *param_4 = local_18;
      param_4[1] = uStack_14;
      sadm_get_spend_byte(&local_1c);
      *(bool *)param_5 = local_1c != 0;
      *param_3 = 1;
      *param_2 = 0;
      return 0;
    }
    *param_3 = 0;
    *param_2 = 3;
    uVar1 = 0;
  }
  else {
    printk("zte_api_sw_port_get_port_multicastrate:Invalid Switch Port %d\n",param_1);
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

