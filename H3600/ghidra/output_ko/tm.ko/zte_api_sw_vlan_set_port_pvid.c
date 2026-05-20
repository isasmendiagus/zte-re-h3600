// module: tm.ko
// function: zte_api_sw_vlan_set_port_pvid @ 0x642f0
// size: 108 bytes
//

undefined4
zte_api_sw_vlan_set_port_pvid(undefined4 param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0xfff < param_2) {
    printk("%s:invaild vlan id\n","zte_api_sw_vlan_set_port_pvid",param_3,param_4,param_4);
    return 0xffffffff;
  }
  if (param_3 < 8) {
    iVar1 = tm_port_pvid_set();
    if (iVar1 == 0) {
      return 0;
    }
    printk("[%s] L%d sw api set failed!\n","zte_api_sw_vlan_set_port_pvid",0x596);
    return 0xffffffff;
  }
  printk("%s:invalid priority value\n","zte_api_sw_vlan_set_port_pvid",param_3,param_4,param_4);
  return 0xffffffff;
}

