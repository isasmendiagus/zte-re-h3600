// module: switch.ko
// function: sw_set_p2pmode @ 0x13680
// size: 44 bytes
//

void sw_set_p2pmode(void)

{
  code cVar1;
  
  cVar1 = tm_vlan_check_ena_set;
  printk("sw_set_uni_as_wan uni=%d\n",tm_vlan_check_ena_set);
  tm_set_p2pmode(cVar1);
  return;
}

