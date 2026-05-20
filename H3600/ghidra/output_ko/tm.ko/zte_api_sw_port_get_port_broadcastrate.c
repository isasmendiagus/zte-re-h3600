// module: tm.ko
// function: zte_api_sw_port_get_port_broadcastrate @ 0x634b8
// size: 180 bytes
//

undefined4
zte_api_sw_port_get_port_broadcastrate
          (uint param_1,undefined1 *param_2,undefined1 *param_3,undefined4 *param_4,
          undefined4 param_5)

{
  undefined4 uVar1;
  char local_19;
  undefined4 local_18;
  int local_14;
  
  if (param_1 < 8) {
    tm_port_cast_rate_limit_get(param_1,&local_19,&local_18,1);
    if (local_19 != '\0') {
      param_4[1] = 0;
      *param_4 = local_18;
      sadm_get_spend_byte(&local_14);
      *(bool *)param_5 = local_14 != 0;
      *param_3 = 1;
      *param_2 = 0;
      return 0;
    }
    *param_3 = 0;
    *param_2 = 3;
    uVar1 = 0;
  }
  else {
    printk("zte_api_sw_port_get_port_broadcastrate:Invalid Switch Port %d\n",param_1);
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

