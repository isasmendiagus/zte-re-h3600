// module: tm.ko
// function: zte_api_sw_port_get_port_ratelimit @ 0x63134
// size: 328 bytes
//

undefined4
zte_api_sw_port_get_port_ratelimit
          (uint param_1,char *param_2,undefined1 *param_3,undefined4 *param_4,undefined1 *param_5)

{
  uint uVar1;
  char cVar2;
  char local_2d;
  int local_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  
  if (7 < param_1) {
    printk("zte_api_sw_port_set_port_ratelimit:Invalid Switch Port %d\n",param_1);
    return 0xffffffff;
  }
  uVar1 = param_1;
  if (5 < param_1) {
    uVar1 = param_1 - 1;
  }
  tm_port_egress_traffic_sharp_get(uVar1,&local_2d,&local_28);
  if (local_2d == '\0') {
    cVar2 = '\x03';
  }
  else {
    *param_4 = local_28;
    param_4[1] = uStack_24;
    sch_get_spend_byte(&local_2c);
    if (local_2c == 0) {
      *param_5 = 0;
    }
    else {
      *param_5 = 1;
    }
    cVar2 = '\x01';
  }
  if (param_1 < 5) {
    tm_port_rate_limit_get(param_1,&local_2d,&local_28);
  }
  else if (param_1 != 5) {
    tm_wifi_ssid_rate_limit_get(param_1 - 5,&local_2d,&local_28);
  }
  if (local_2d == '\0') {
    if (cVar2 == '\x03') {
      *param_3 = 0;
      *param_2 = '\x03';
      return 0;
    }
  }
  else if (cVar2 == '\x01') {
    cVar2 = '\x02';
  }
  else {
    *param_4 = local_28;
    param_4[1] = uStack_24;
    sadm_get_spend_byte(&local_2c);
    if (local_2c == 0) {
      *param_5 = 0;
      cVar2 = '\0';
    }
    else {
      cVar2 = '\0';
      *param_5 = 1;
    }
  }
  *param_3 = 1;
  *param_2 = cVar2;
  return 0;
}

