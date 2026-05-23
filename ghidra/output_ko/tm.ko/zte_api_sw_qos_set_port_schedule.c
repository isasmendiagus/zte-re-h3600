// module: tm.ko
// function: zte_api_sw_qos_set_port_schedule @ 0x6356c
// size: 64 bytes
//

undefined4 zte_api_sw_qos_set_port_schedule(undefined4 param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  
  if (1 < param_3) {
    printk("zte_api_sw_port_set_port_ratelimit:input invalid parameter!\n");
    return 0xffffffff;
  }
  iVar1 = tm_port_egress_spdwrr_schedule_set();
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_port_egress_spdwrr_schedule_set fail\n");
  return 0xffffffff;
}

