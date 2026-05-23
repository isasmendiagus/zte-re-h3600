// module: tm.ko
// function: zte_api_sw_port_set_port_ratelimit @ 0x62fb0
// size: 388 bytes
//

undefined4
zte_api_sw_port_set_port_ratelimit
          (uint param_1,uint param_2,int param_3,undefined4 param_4,int param_5,int param_6,
          char param_7)

{
  undefined4 uVar1;
  int iVar2;
  
  if (7 < param_1) {
    printk("zte_api_sw_port_set_port_ratelimit:Invalid Switch Port %d\n",param_1,param_3,param_4,
           param_4);
    return 0xffffffff;
  }
  if (param_5 == 0 && param_6 == 0) {
    param_3 = 0;
  }
  if ((param_2 & 0xfd) != 0) goto LAB_00063024;
  if (param_7 == '\0') {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x18;
  }
  iVar2 = sadm_set_spend_byte(uVar1);
  if (iVar2 != 0) {
    printk("sadm_set_spend_byte fail!\n");
    return 0xffffffff;
  }
  if (param_3 == 0) {
    if (param_1 < 5) {
      tm_port_rate_limit_set(param_1,0,0,0);
      goto LAB_00063024;
    }
    if (param_1 != 5) {
      tm_wifi_ssid_rate_limit_set(param_1 - 5,0,0,0);
      goto LAB_00063024;
    }
  }
  else {
    if (param_1 < 5) {
      tm_port_rate_limit_set(param_1,param_3,param_5,param_6);
      goto LAB_00063024;
    }
    if (param_1 != 5) {
      tm_wifi_ssid_rate_limit_set(param_1 - 5,param_3,param_5,param_6);
      goto LAB_00063024;
    }
  }
  printk("PON port don\'t support ingress ratelimit!\n");
LAB_00063024:
  if (1 < param_2 - 1) {
    return 0;
  }
  if (param_7 == '\0') {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x14;
  }
  iVar2 = sch_set_spend_byte(uVar1);
  if (iVar2 != 0) {
    printk("sch_set_spend_byte fail!\n");
    return 0xffffffff;
  }
  if (param_1 - 6 < 2) {
    param_1 = param_1 - 1 & 0xff;
  }
  if (param_3 == 0) {
    tm_port_egress_traffic_sharp_set(param_1,0,0);
    return 0;
  }
  tm_port_egress_traffic_sharp_set(param_1,param_3,param_5);
  return 0;
}

