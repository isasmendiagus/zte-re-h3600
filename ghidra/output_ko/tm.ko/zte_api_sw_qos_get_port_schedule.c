// module: tm.ko
// function: zte_api_sw_qos_get_port_schedule @ 0x635ac
// size: 36 bytes
//

undefined4 zte_api_sw_qos_get_port_schedule(void)

{
  int iVar1;
  
  iVar1 = tm_port_egress_spdwrr_schedule_get();
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_port_egress_spdwrr_schedule_get fail\n");
  return 0xffffffff;
}

