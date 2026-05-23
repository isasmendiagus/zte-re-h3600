// module: switch.ko
// function: sw_set_p2pmode @ 0x13720
// size: 44 bytes
//

void sw_set_p2pmode(void)

{
  code cVar1;
  
  cVar1 = zte_api_sw_mac_set_port_learnlimit;
  printk("sw_set_uni_as_wan uni=%d\n",zte_api_sw_mac_set_port_learnlimit);
  tm_set_p2pmode(cVar1);
  return;
}

