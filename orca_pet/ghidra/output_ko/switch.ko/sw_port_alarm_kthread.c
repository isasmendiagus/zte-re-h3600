// module: switch.ko
// function: sw_port_alarm_kthread @ 0x16fb8
// size: 236 bytes
//

void sw_port_alarm_kthread(void)

{
  int iVar1;
  int iVar2;
  
  do {
    if (g_ethdev_carrierFlag != 0) {
      sw_alarm_scanforalarm();
    }
    if ((l_clk_48835 < 0x5a) && (l_clk_48835 = l_clk_48835 + 1, l_clk_48835 == 0x5a)) {
      l_clk_48835 = 0x5a;
      iVar1 = 1;
      do {
        tm_protocol_pkt_limit_pps_set(0,iVar1,0,0);
        iVar2 = iVar1 + 1;
        tm_protocol_pkt_limit_pps_set(1,iVar1,0,0);
        iVar1 = iVar2;
      } while (iVar2 != 8);
      zte_api_sw_port_set_port_ratelimit(6,1,0);
      zte_api_sw_port_set_port_ratelimit(7,1,0);
      l_clk_48835 = 0x5b;
    }
    msleep_interruptible(sw_timerbase * 500);
  } while( true );
}

