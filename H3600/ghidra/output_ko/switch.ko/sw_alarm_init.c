// module: switch.ko
// function: sw_alarm_init @ 0x16fe0
// size: 236 bytes
//

undefined4 sw_alarm_init(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  __memzero(portalarmstat,0x40);
  uVar1 = kthread_create_on_node(sw_port_alarm_kthread,0,0xffffffff,"sw_port_alarm_kthread");
  if (uVar1 < 0xfffff001) {
    wake_up_process();
  }
  printk("[SW]set cpu queue rate limit to 8000pps\n");
  iVar2 = 1;
  do {
    tm_protocol_pkt_limit_pps_set(0,iVar2,1,8000);
    iVar3 = iVar2 + 1;
    tm_protocol_pkt_limit_pps_set(1,iVar2,1,8000);
    iVar2 = iVar3;
  } while (iVar3 != 7);
  tm_protocol_pkt_limit_pps_set(0,7,1,8000);
  zte_api_sw_port_set_port_ratelimit(6,1,1);
  zte_api_sw_port_set_port_ratelimit(7,1,1);
  fpga_write_reg(0xd3000,0x1f40fa0);
  return 0;
}

