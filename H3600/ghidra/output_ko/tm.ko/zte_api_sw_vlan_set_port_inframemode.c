// module: tm.ko
// function: zte_api_sw_vlan_set_port_inframemode @ 0x61e34
// size: 212 bytes
//

undefined4
zte_api_sw_vlan_set_port_inframemode
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = tm_port_pkt_filter_set(param_1,1,param_3,param_4,param_4);
  if (iVar1 != 0) {
    printk("[%s] L%d sw api set failed!\n","zte_api_sw_vlan_set_port_inframemode",0x542);
    return 0xffffffff;
  }
  switch(param_2) {
  case 0:
    iVar1 = tm_port_vlan_filter_set(param_1,0);
    if (iVar1 == 0) {
      return 0;
    }
    break;
  case 1:
    iVar1 = tm_port_vlan_filter_set(param_1,0x3f);
    if (iVar1 == 0) {
      return 0;
    }
    break;
  case 2:
    iVar1 = tm_port_vlan_filter_set(param_1,1);
    if (iVar1 == 0) {
      return 0;
    }
    break;
  case 3:
    iVar1 = tm_port_vlan_filter_set(param_1,0x3e);
    if (iVar1 == 0) {
      return 0;
    }
    break;
  default:
    printk("[%s] input invalid mode\n","zte_api_sw_vlan_set_port_inframemode");
    return 0xffffffff;
  }
  printk("[%s] L%d sw api set failed!\n","zte_api_sw_vlan_set_port_inframemode",0x55b);
  return 0xffffffff;
}

